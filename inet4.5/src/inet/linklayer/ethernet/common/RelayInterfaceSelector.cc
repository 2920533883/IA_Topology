//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "inet/linklayer/ethernet/common/RelayInterfaceSelector.h"

#include "inet/common/DirectionTag_m.h"
#include "inet/common/ProtocolUtils.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/VlanTag_m.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace inet {

Define_Module(RelayInterfaceSelector);

void RelayInterfaceSelector::initialize(int stage)
{
    PacketPusherBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        macForwardingTable.reference(this, "macTableModule", true);
        interfaceTable.reference(this, "interfaceTableModule", true);
        WATCH(numProcessedFrames);
        WATCH(numDroppedFrames);
    }
}

cGate *RelayInterfaceSelector::getRegistrationForwardingGate(cGate *gate)
{
    if (gate == outputGate)
        return inputGate;
    else if (gate == inputGate)
        return outputGate;
    else
        throw cRuntimeError("Unknown gate");
}

void RelayInterfaceSelector::pushPacket(Packet *packet, cGate *gates)
{
    Enter_Method("pushPacket");
    take(packet);
    std::string name = packet->getName();
    if(name.find("app") != std::string::npos){
        size_t start_a = name.find('[');
        start_a += 1; // 移到数字的开始
        size_t end_a = name.find(']', start_a);
        std::string a_str = name.substr(start_a, end_a - start_a);
        int flow_index = std::stoi(a_str)-1;
        size_t last_dash = name.rfind('-');
        std::string c_str = name.substr(last_dash + 1);
        int jump_index = std::stoi(c_str);
        std::string filePath = par("filePath");
        std::ifstream infile(filePath);
        std::string line;
        int lineNumber = 0;
        std::vector<int> ports;
        // 逐行读取文件
        while (std::getline(infile, line)) {
            if (lineNumber == flow_index){
                std::istringstream iss(line);
                int port;
                // 逐个解析每个端口号
                while (iss >> port) {
                    ports.push_back(port);
                }
                break;
            }
            lineNumber++;
        }
        infile.close();
        EV << flow_index << " " << jump_index << ports[jump_index]<< EV_ENDL;
        packet->removeTagIfPresent<InterfaceReq>();
        packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(100+ports[jump_index]);
        name.replace(last_dash + 1, c_str.length(), std::to_string(jump_index+1));
        packet->setName(name.c_str());
    }
    auto interfaceReq = packet->findTag<InterfaceReq>();
    auto macAddressReq = packet->getTag<MacAddressReq>();
    auto destinationAddress = macAddressReq->getDestAddress();
    if (interfaceReq != nullptr) {
        auto networkInterface = interfaceTable->getInterfaceById(interfaceReq->getInterfaceId());
        sendPacket(packet, destinationAddress, networkInterface);
    }
    else {
        auto interfaceInd = packet->findTag<InterfaceInd>();
        auto incomingInterface = interfaceInd != nullptr ? interfaceTable->getInterfaceById(interfaceInd->getInterfaceId()) : nullptr;
        auto vlanReq = packet->findTag<VlanReq>();
        int vlanId = vlanReq != nullptr ? vlanReq->getVlanId() : 0;
        if (destinationAddress.isBroadcast())
            broadcastPacket(packet, destinationAddress, incomingInterface);
        else if (destinationAddress.isMulticast()) {
            auto outgoingInterfaceIds = macForwardingTable->getMulticastAddressForwardingInterfaces(destinationAddress, vlanId);
            if (outgoingInterfaceIds.size() == 0)
                broadcastPacket(packet, destinationAddress, incomingInterface);
            else {
                for (auto outgoingInterfaceId : outgoingInterfaceIds) {
                    if (interfaceInd != nullptr && outgoingInterfaceId == interfaceInd->getInterfaceId())
                        EV_WARN << "Ignoring outgoing interface because it is the same as incoming interface" << EV_FIELD(destinationAddress) << EV_FIELD(incomingInterface) << EV_FIELD(packet) << EV_ENDL;
                    else {
                        auto outgoingInterface = interfaceTable->getInterfaceById(outgoingInterfaceId);
                        sendPacket(packet->dup(), destinationAddress, outgoingInterface);
                    }
                }
                delete packet;
            }
        }
        else {
            // Find output interface of destination address and send packet to output interface
            // if not found then broadcasts to all other interfaces instead
            int outgoingInterfaceId = macForwardingTable->getUnicastAddressForwardingInterface(destinationAddress, vlanId);
            // should not send out the same packet on the same interface
            // (although wireless interfaces are ok to receive the same message)
            if (interfaceInd != nullptr && outgoingInterfaceId == interfaceInd->getInterfaceId()) {
                EV_WARN << "Discarding packet because outgoing interface is the same as incoming interface" << EV_FIELD(destinationAddress) << EV_FIELD(incomingInterface) << EV_FIELD(packet) << EV_ENDL;
                numDroppedFrames++;
                PacketDropDetails details;
                details.setReason(NO_INTERFACE_FOUND);
                emit(packetDroppedSignal, packet, &details);
                delete packet;
            }
            else if (outgoingInterfaceId != -1) {
                auto outgoingInterface = interfaceTable->getInterfaceById(outgoingInterfaceId);
                sendPacket(packet, destinationAddress, outgoingInterface);
            }
            else
                broadcastPacket(packet, destinationAddress, incomingInterface);
        }
    }
    numProcessedFrames++;
    updateDisplayString();
}

void RelayInterfaceSelector::broadcastPacket(Packet *outgoingPacket, const MacAddress& destinationAddress, NetworkInterface *incomingInterface)
{
    if (incomingInterface == nullptr)
        EV_INFO << "Broadcasting packet to all interfaces" << EV_FIELD(destinationAddress) << EV_FIELD(outgoingPacket) << EV_ENDL;
    else
        EV_INFO << "Broadcasting packet to all interfaces except incoming interface" << EV_FIELD(destinationAddress) << EV_FIELD(incomingInterface) << EV_FIELD(outgoingPacket) << EV_ENDL;
    for (int i = 0; i < interfaceTable->getNumInterfaces(); i++) {
        auto outgoingInterface = interfaceTable->getInterface(i);
        if (incomingInterface != outgoingInterface && isForwardingInterface(outgoingInterface))
            sendPacket(outgoingPacket->dup(), destinationAddress, outgoingInterface);
    }
    delete outgoingPacket;
}

void RelayInterfaceSelector::sendPacket(Packet *packet, const MacAddress& destinationAddress, NetworkInterface *outgoingInterface)
{
    EV_INFO << "Sending packet to peer" << EV_FIELD(destinationAddress) << EV_FIELD(outgoingInterface) << EV_FIELD(packet) << EV_ENDL;
    packet->addTagIfAbsent<DirectionTag>()->setDirection(DIRECTION_OUTBOUND);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(outgoingInterface->getInterfaceId());
    if (auto outgoingInterfaceProtocol = outgoingInterface->getProtocol())
        ensureEncapsulationProtocolReq(packet, outgoingInterfaceProtocol, true, false);
    setDispatchProtocol(packet);
    pushOrSendPacket(packet, outputGate, consumer);
}

} // namespace inet


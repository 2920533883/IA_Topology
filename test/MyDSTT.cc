#include <omnetpp.h>
#include <string.h>
#include <vector>
#include <map>
#include "inet/linklayer/ethernet/basic/EthernetEncapsulation.h"
#include "inet/linklayer/ethernet/basic/EthernetMac.h"
#include "inet/common/TagBase.h"
#include "inet/physicallayer/wired/ethernet/EthernetPhyHeader_m.h"
#include "inet/linklayer/ieee8021q/Ieee8021qTagHeader_m.h"
#include "inet/transportlayer/udp/UdpHeader_m.h"
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/DscpTag_m.h"
#include "inet/networklayer/common/EcnTag_m.h"
#include "inet/networklayer/arp/ipv4/GlobalArp.h"
#include "inet/networklayer/common/MyTag.h"
#include "inet/linklayer/ppp/PppFrame_m.h"
#include "inet/networklayer/common/TosTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"

using namespace inet;
using namespace omnetpp;
using namespace std;
class MyDSTT : public cSimpleModule{
        int localPort;
        int destPort;
        L3Address destAddress;
        UdpSocket socket;
        MacAddress srcMacAddress;
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void sendPacket(Packet *pkt);

};

Define_Module(MyDSTT);


void MyDSTT::initialize()
{
    destPort = par("destPort");
    localPort = par("localPort");
}
void MyDSTT::sendPacket(Packet *pkt)
{
    socket.setOutputGate(gate("upperLayerOut"));
    socket.bind(localPort);
    int tos = par("tos");
    if (tos != -1)
        socket.setTos(tos);
    if (destAddress.isUnspecified())
        destAddress = L3AddressResolver().resolve(par("destAddress"));
    Packet* packet = new Packet();
    packet->insertAtBack(pkt->peekAll());
    socket.sendTo(packet, destAddress, destPort);
    socket.close();
}

void MyDSTT::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(),"closed") == 0) {
        EV << "closed bind" << endl;
    }
    else if (strcmp(msg->getArrivalGate()->getName(),"upperLayerIn") == 0){
        Packet *pkt = check_and_cast<Packet *>(msg);
        pkt->removeTagIfPresent<InterfaceInd>();
        pkt->removeTagIfPresent<NetworkProtocolInd>();
        pkt->removeTagIfPresent<DscpInd>();
        pkt->removeTagIfPresent<EcnInd>();
        pkt->removeTagIfPresent<TosInd>();
        pkt->removeTagIfPresent<L3AddressInd>();
        pkt->removeTagIfPresent<HopLimitInd>();
        pkt->removeTagIfPresent<PacketProtocolTag>();
        pkt->removeTagIfPresent<InterfaceInd>();
        pkt->removeTagIfPresent<DispatchProtocolReq>();
        auto eph = pkt->popAtFront<EthernetPhyHeader>();
        auto emh = pkt->popAtFront<EthernetMacHeader>();
        // get srcAddress
        MacAddress* src = new MacAddress(srcMacAddress);
        const MacAddress& new_mac = *src;
        const auto& new_emh = makeShared<EthernetMacHeader>();
        new_emh->setChunkLength(emh->getChunkLength());
        new_emh->setSrc(emh->getSrc());
        new_emh->setDest(new_mac);
        new_emh->setTypeOrLength(emh->getTypeOrLength());
        pkt->insertAtFront(new_emh);
        Packet* newPkt = new Packet(*pkt);
        send(newPkt, "lowerLayerOut");
    }
    else {
        EV << msg->getArrivalGate()->getName() << EV_ENDL;
        Packet *pkt = check_and_cast<Packet *>(msg);
        auto emh = pkt->popAtFront<EthernetMacHeader>();
        srcMacAddress = emh->getSrc();
        sendPacket(pkt);
    }
}

//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
import inet.linklayer.contract.IEthernetInterface;
import inet.linklayer.ethernet.contract.IEthernetMacLayer;
import inet.networklayer.common.NetworkInterface;
import inet.physicallayer.wired.ethernet.IEthernetPhyLayer;
import inet.protocolelement.measurement.IMeasurementLayer;
import inet.protocolelement.processing.IProcessingDelayLayer;
import inet.protocolelement.trafficconditioner.ITrafficConditionerLayer;
import *;

//
// This module implements an Ethernet network interface.
//
module NWTTInterface extends NetworkInterface like IEthernetInterface
{
    parameters:
        string protocol = default("ethernetmac");
        bool broadcast = default(true);
        bool multicast = default(true);
        string address @mutable = default("auto");
        double bitrate @unit(bps);
        int mtu @unit(B) = default(1500B);
        string interfaceTableModule;
        *.bitrate = default(this.bitrate);
        @display("bgb=486.19998,400.4");
    //        macLayer.queue.typename = default("Ieee8021qTimeAwareShaper");
    gates:
        input upperLayerIn;
        output upperLayerOut;
        inout phys @labels(EthernetSignal);
    submodules:
        macLayer: <default("EthernetMacLayer")> like IEthernetMacLayer {
            parameters:
                @display("p=283,250");
        }
        phyLayer: <default("EthernetPhyLayer")> like IEthernetPhyLayer {
            parameters:
                transmitter.clockModule = default("");
                @display("p=403,250");
        }
        NWTT: MyNWTT {
            parameters:
                @display("p=184,256");
        }
    connections allowunconnected:
         upperLayerIn --> { @display("m=n"); } --> NWTT.upperLayerIn;
        NWTT.lowerLayerOut --> macLayer.upperLayerIn;
        macLayer.upperLayerOut --> NWTT.lowerLayerIn;
        NWTT.upperLayerOut --> upperLayerOut;
        macLayer.lowerLayerOut --> phyLayer.upperLayerIn;
        phyLayer.lowerLayerOut --> { @display("m=s"); } --> phys$o;

        phys$i --> { @display("m=s"); } --> phyLayer.lowerLayerIn;
        phyLayer.upperLayerOut --> macLayer.lowerLayerIn;
}

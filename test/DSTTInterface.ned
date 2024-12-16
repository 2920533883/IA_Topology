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
module DSTTInterface extends NetworkInterface like IEthernetInterface
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
    //        macLayer.queue.typename = default("Ieee8021qTimeAwareShaper");
    gates:
        input upperLayerIn;
        output upperLayerOut;
        input cutthroughIn @loose;
        output cutthroughOut @loose;
        inout phys @labels(EthernetSignal);
    submodules:

        macLayer: <default("EthernetMacLayer")> like IEthernetMacLayer {
            parameters:
                @display("p=244,245");
        }
        phyLayer: <default("EthernetPhyLayer")> like IEthernetPhyLayer {
            parameters:
                transmitter.clockModule = default("");
                @display("p=222,368");
        }
        DSTT: MyDSTT {
            parameters:
                @display("p=222,36");
        }
    connections allowunconnected:
        upperLayerIn --> DSTT.upperLayerIn;
        DSTT.lowerLayerOut --> macLayer.upperLayerIn;
        macLayer.lowerLayerOut --> phyLayer.upperLayerIn;
        phyLayer.lowerLayerOut --> { @display("m=s"); } --> phys$o;

        phys$i --> { @display("m=s"); } --> phyLayer.lowerLayerIn;
        phyLayer.upperLayerOut --> macLayer.lowerLayerIn;
        macLayer.upperLayerOut --> DSTT.lowerLayerIn;
        DSTT.upperLayerOut --> upperLayerOut;

}

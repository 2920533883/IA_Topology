package d2d;
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//package tsn5g.simulations;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import simu5g.common.binder.Binder;
import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.nodes.Upf;
import simu5g.nodes.NR.gNodeB;
import simu5g.nodes.NR.NRUe;
import inet.node.tsn.*;
import inet.node.ethernet.*;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.networks.base.TsnNetworkBase;
import *;
network S2C extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
        @display("bgb=1747.6351,932.99255");
    submodules:
        carrierAggregation: CarrierAggregation {
            @display("p=1479.2579,399.09598");
        }
        channelControl: LteChannelControl {
            @display("p=1477.812,52.056;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=1479.2579,187.98;is=s");
        }
        binder: Binder {
            @display("p=1479.2579,294.98398;is=s");
        }
        Server: TsnDevice {
            @display("p=1247.5875,212.30875");
        }
        tsnSwitch: TsnSwitch {
            @display("p=985.26996,334.62");
        }
        upf: MyUpf {
            NWTT.bitrate = 100Mbps;
            @display("p=682.76,251.81");
        }
        gnb: gNodeB {
            @display("p=632.06,449.53998;is=vl");
        }
        Client1: TsnDevice {
            @display("p=411.485,367.71");
        }
        u1: TsnUe {
            DSTT.bitrate = 100Mbps;
            @display("p=432.69907,350.2;is=vs");
        }
        Client2: TsnDevice {
            @display("p=397.34235,648.2068");
        }
        u2: TsnUe {
            DSTT.bitrate = 100Mbps;
            @display("p=410.81155,631.37024;is=vs");
        }
    connections:
        Client1.ethg++ <--> Eth100M{length=0m;} <--> u1.phys;
        Client2.ethg++ <--> Eth100M{length=0m;} <--> u2.phys;
        upf.filterGate <--> Eth100M <--> tsnSwitch.ethg++;
        tsnSwitch.ethg++ <--> Eth100M <--> Server.ethg++;
        upf.pppg++ <--> Eth100M <--> gnb.ppp;
}


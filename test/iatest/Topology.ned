package iatest;
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
import inet.common.scenario.ScenarioManager;
network Topology
{
    parameters:
        // kong tiao
        int numHVAC = 8;
        **.bitrate = default(100Mbps);

    submodules:
        scenarioManager: ScenarioManager {
            @display("p=74.36,398.84");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=100,27;is=s");
        }
        channelControl: LteChannelControl {
            @display("p=196,27;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,300;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=176,88;is=s");
        }
        binder: Binder {
            @display("p=176,200;is=s");
        }
        server: TsnDevice {
            @display("p=800,20.39");
        }
        switch1: TsnSwitch {
            @display("p=500,197.73");
        }
        switch2: TsnSwitch {
            @display("p=700,197.73");
        }
        switch3: TsnSwitch {
            @display("p=900,197.73");
        }
        switch4: TsnSwitch {
            @display("p=1100,197.73");
        }
        switch5: TsnSwitch {
            @display("p=600,128.44");
        }
        switch6: TsnSwitch {
            @display("p=1000,128.44");
        }
        switch7: TsnSwitch {
            @display("p=800,87");
        }
        HVACClient[numHVAC]: TsnDevice {

            @display("i=device/card;p=450,350,r,100;is=s;");
        }


    connections:
        for i=0..1 {
            HVACClient[i].ethg++ <--> Eth100M <--> switch1.ethg++;
        }
        for i=2..3 {
            HVACClient[i].ethg++ <--> Eth100M <--> switch2.ethg++;
        }
        for i=4..5 {
            HVACClient[i].ethg++ <--> Eth100M <--> switch3.ethg++;
        }
        for i=6..7 {
            HVACClient[i].ethg++ <--> Eth100M <--> switch4.ethg++;
        }
        switch1.ethg++ <--> Eth100M <--> switch5.ethg++;
        switch2.ethg++ <--> Eth100M <--> switch5.ethg++;
        switch3.ethg++ <--> Eth100M <--> switch6.ethg++;
        switch4.ethg++ <--> Eth100M <--> switch6.ethg++;
        switch1.ethg++ <--> Eth100M <--> switch2.ethg++;
        switch2.ethg++ <--> Eth100M <--> switch3.ethg++;
        switch3.ethg++ <--> Eth100M <--> switch4.ethg++;
        switch7.ethg++ <--> Eth100M <--> server.ethg++;
        switch6.ethg++ <--> Eth100M <--> switch7.ethg++;
        switch5.ethg++ <--> Eth100M <--> switch7.ethg++;
}

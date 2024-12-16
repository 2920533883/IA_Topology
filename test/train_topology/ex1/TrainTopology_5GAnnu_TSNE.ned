package train_topology.ex1;
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
network TrainTopology_5GAnnu_TSNE
{
    parameters:
        // kong tiao
        int numHVAC = 8;
        // men kong
        int numDCU = 8;
        // dianchi
        int numBC = 8;
        // che xiang
        int numPIS = 8;
        // qian yin
        int numTCU = 8;
        // zhi dong
        int numBCU = 8;
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
            @display("p=766,56");
        }
        switch1: TsnSwitch {
            @display("p=645,199");
        }
        switch2: TsnSwitch {
            @display("p=998,211");
        }
        switch3: TsnSwitch {
            @display("p=785,135");
        }
        upf1: MyUpf {
            @display("p=581,266;is=s");
        }
        upf2: MyUpf {
            @display("p=1017,277;is=s");
        }
        gnbL1: gNodeB {
            gateway = "upf1";
            @display("p=432,325");
        }

        gnbL2: gNodeB {
            gateway = "upf1";
            @display("p=621,325");
        }
        gnbL3: gNodeB {
            gateway = "upf1";
            @display("p=818,325");
        }
        gnbL4: gNodeB {
            gateway = "upf1";
            @display("p=977,331");
        }

        gnbR1: gNodeB {
            gateway = "upf2";
            @display("p=475,379");
        }

        gnbR2: gNodeB {
            gateway = "upf2";
            @display("p=621,379");
        }
        gnbR3: gNodeB {
            gateway = "upf2";
            @display("p=854,388");
        }
        gnbR4: gNodeB {
            gateway = "upf2";
            @display("p=1004,388");
        }
        HVACClient[numHVAC]: TsnDevice {

            @display("i=device/card;p=450,450,r,100;is=s;");
        }
        HVACUe[numHVAC]: TsnUe {
            @display("i=device/card;is=s;");
        }
        BCClient[numBC]: TsnDevice {
            @display("i=device/card;p=450,500,r,100;is=s;");
        }
        BCUe[numBC]: TsnUe {
            @display("i=device/card;is=s;");
        }
        TCUClient[numTCU]: TsnDevice {
            @display("i=device/card;p=450,550,r,100;is=s;");
        }
        TCUUe[numTCU]: TsnUe {
            @display("i=device/card;is=s;");
        }
        BCUClient[numBCU]: TsnDevice {
            @display("i=device/device;p=450,600,r,100;is=s;");
        }
        BCUUe[numBCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
        PISClient[numPIS]: TsnDevice {
            @display("i=device/device;p=450,650,r,100;is=s;");
        }
        PISUe[numPIS]: TsnUe {
            @display("i=device/device;is=s;");
        }
        DCUClient[numDCU]: TsnDevice {
            @display("i=device/device;p=450,700,r,100;is=s;");
        }
        DCUUe[numDCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
        TTCUClient[numTCU]: TsnDevice {
            @display("i=device/device;p=450,750,r,100;is=s;");
        }
        TTCUUe[numTCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
    connections:
        for i=0..numHVAC-1 {
            HVACClient[i].ethg++ <--> Eth100M <--> HVACUe[i].phys;
        }
        for i=0..numBC-1 {
            BCClient[i].ethg++ <--> Eth100M <--> BCUe[i].phys;
        }
        for i=0..numDCU-1 {
            DCUClient[i].ethg++ <--> Eth100M <--> DCUUe[i].phys;
        }
        for i=0..numPIS-1 {
            PISClient[i].ethg++ <--> Eth100M <--> PISUe[i].phys;
        }
        for i=0..numTCU-1 {
            TCUClient[i].ethg++ <--> Eth100M <--> TCUUe[i].phys;
            TTCUClient[i].ethg++ <--> Eth100M <--> TTCUUe[i].phys;
        }
        for i=0..numBCU-1 {
            BCUClient[i].ethg++ <--> Eth100M <--> BCUUe[i].phys;
        }

        switch1.ethg++ <--> Eth100M <--> upf1.filterGate;
        switch2.ethg++ <--> Eth100M <--> upf2.filterGate;
        switch1.ethg++ <--> Eth100M <--> switch3.ethg++;
        switch2.ethg++ <--> Eth100M <--> switch3.ethg++;
        gnbL1.ppp <--> Eth100M <--> upf1.pppg++;
        gnbL1.x2++ <--> Eth100M <--> gnbL2.x2++;
        gnbL3.x2++ <--> Eth100M <--> gnbL4.x2++;
        gnbL2.x2++ <--> Eth100M <--> gnbL3.x2++;
        gnbL4.x2++ <--> Eth100M <--> gnbL1.x2++;
        gnbR4.ppp <--> Eth100M <--> upf2.pppg++;
        gnbR4.x2++ <--> Eth100M <--> gnbR3.x2++;
        gnbR2.x2++ <--> Eth100M <--> gnbR1.x2++;
        gnbR3.x2++ <--> Eth100M <--> gnbR2.x2++;
        gnbR1.x2++ <--> Eth100M <--> gnbR4.x2++;
        switch3.ethg++ <--> Eth100M <--> server.ethg++;
}

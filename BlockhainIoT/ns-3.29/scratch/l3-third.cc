/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"

//  Network Topology
//       VLAN1                   VLAN2
//    Wifi 10.1.2.0          Wifi 10.1.3.0
//            AP            AP
//       *    *             *    *
//       |    |             |    |
//      n3   n0     n1     n2   n4
//            |      |      |
//            ================
//              LAN 10.1.3.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ThirdScriptExample");

int main(int argc, char *argv[]) {

	CommandLine cmd;
	cmd.Parse(argc, argv);

	//Create a bus topology
	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
	csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

	NodeContainer csmaNodes;
	csmaNodes.Create(3);
	NetDeviceContainer csmaDevices = csma.Install(csmaNodes);

	//Create two wi-fi networks with adjacent bus nodes:
	NodeContainer vlan1Nodes;
	vlan1Nodes.Create(2);
	NodeContainer vlan1Ap;
    vlan1Ap.Add(csmaNodes.Get(0));

	NodeContainer vlan2Nodes;
	vlan2Nodes.Create(2);
	NodeContainer vlan2Ap;
	vlan2Ap.Add(csmaNodes.Get(2));

	//Следующий фрагмент кода обеспечивает моделирование wi-fi устройств и
	//канала связи между ними.
	//Настройка PHY уровеня и канала связи
	YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
	YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default();
	phy1.SetChannel(channel.Create());
	YansWifiPhyHelper phy2 = YansWifiPhyHelper::Default();
	phy2.SetChannel(channel.Create());

	//После того как уровень PHY настроен, перейдём к настройке уровня MAC
	//в беспроводных сетях
	WifiHelper wifi;
	wifi.SetRemoteStationManager("ns3::AarfWifiManager");

	//Данный код создаёт сервис 802.11, устанавливает
	//его тип равным «ns3 :: StaWifiMac», SSID равным «ns-3-ssid»
	// и значение атрибута
	//ActiveProbing (активировать зондирование) с типом «false».
	WifiMacHelper vlan1Mac;
	Ssid ssid = Ssid("vlan1-ssid");
	vlan1Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer vlan1Devices = wifi.Install(phy1, vlan1Mac, vlan1Nodes);
	vlan1Mac.SetType("ns3::ApWifiMac","Ssid", SsidValue (ssid));
	NetDeviceContainer vlan1ApDevice = wifi.Install(phy1, vlan1Mac, vlan1Ap);

	WifiMacHelper vlan2Mac;
	Ssid ssid2 = Ssid("vlan2-ssid");
	vlan2Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid2),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer vlan2Devices = wifi.Install(phy2, vlan2Mac, vlan2Nodes);
	vlan2Mac.SetType("ns3::ApWifiMac","Ssid", SsidValue (ssid2));
	NetDeviceContainer vlan2ApDevice = wifi.Install(phy2, vlan2Mac, vlan2Ap);


	MobilityHelper mobility1;

	mobility1.SetPositionAllocator("ns3::GridPositionAllocator",
				"MinX",	DoubleValue(0.0),
				"MinY", DoubleValue(0.0),
				"DeltaX", DoubleValue(5.0),
				"DeltaY", DoubleValue(10.0),
				"GridWidth",UintegerValue(3),
				"LayoutType", StringValue("RowFirst"));

	mobility1.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility1.Install(vlan1Nodes);

	mobility1.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility1.Install(vlan1Ap);

	MobilityHelper mobility2;

	mobility2.SetPositionAllocator("ns3::GridPositionAllocator",
			"MinX",	DoubleValue(60.0),
			"MinY", DoubleValue(0.0),
			"DeltaX", DoubleValue(5.0),
			"DeltaY", DoubleValue(15.0),
			"GridWidth",UintegerValue(3),
			"LayoutType", StringValue("RowFirst"));

	mobility2.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility2.Install(vlan2Nodes);

	mobility2.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility2.Install(vlan2Ap);

	InternetStackHelper stack;
	stack.Install(csmaNodes);
	stack.Install(vlan1Nodes);
	stack.Install(vlan2Nodes);

	Ipv4AddressHelper address;

	address.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces;
	csmaInterfaces = address.Assign(csmaDevices);

	address.SetBase("10.1.2.0", "255.255.255.0");
	address.Assign(vlan1Devices);
	address.Assign(vlan1ApDevice);

	address.SetBase("10.1.3.0", "255.255.255.0");
	address.Assign(vlan2Devices);
	address.Assign(vlan2ApDevice);

	//Server on the middle node:
	UdpEchoServerHelper echoServer(9);
	ApplicationContainer serverApps = echoServer.Install(csmaNodes.Get(1));
	serverApps.Start(Seconds(1.0));
	serverApps.Stop(Seconds(10.0));

	UdpEchoClientHelper echoClient(csmaInterfaces.GetAddress(1), 9);
	echoClient.SetAttribute("MaxPackets", UintegerValue(5));
	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize", UintegerValue(1024));

	ApplicationContainer clientApp1 = echoClient.Install(vlan1Nodes.Get(0));
	clientApp1.Start(Seconds(2.0));
    clientApp1.Stop(Seconds(10.0));

	ApplicationContainer clientApp2 = echoClient.Install(vlan2Nodes.Get(0));
	clientApp2.Start(Seconds(2.0));
	clientApp2.Stop(Seconds(10.0));

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	Simulator::Stop(Seconds(10.0));

	phy1.EnablePcap("l3", vlan1Devices.Get(0));
	phy2.EnablePcap("l3", vlan2Devices.Get(0));
	csma.EnablePcap("l3", csmaDevices.Get(0), true);

	Simulator::Run();
	Simulator::Destroy();
	return 0;
}

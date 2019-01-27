/*
 * iot-model.cc
 *
 *  Created on: Dec 14, 2018
 *      Author: lika
 */
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

	uint32_t nSpokes = 6;
	CommandLine cmd;
	cmd.Parse(argc, argv);

	NS_LOG_INFO("Build ring topology.");
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
	PointToPointRingHelper ring(nSpokes, pointToPoint);

	NS_LOG_INFO("Install internet stack on all nodes.");
	InternetStackHelper internet;
	ring.InstallStack(internet);

	NS_LOG_INFO("Assign IP Addresses.");
	ring.AssignIpv4Addresses(Ipv4AddressHelper("10.1.1.0", "255.255.255.0"));

	//Another node with a p2p connection to the ring
	//NodeContainer p2pNodes;
	// p2pNodes.Add(ring.GetSpokeNode(nSpokes-1));
	// p2pNodes.Create(1);
	// internet.Install(p2pNodes.Get(1));
	// NetDeviceContainer p2pDevices = pointToPoint.Install(p2pNodes);
	//address.Assign(p2pDevices);

	NodeContainer wifiStaNodes;
	wifiStaNodes.Create(3);
	NodeContainer wifiApNode;
	wifiApNode.Add(ring.Get(0));

	Names::Add("client0", wifiStaNodes.Get(0));
	Names::Add("client1", wifiStaNodes.Get(1));
	Names::Add("client2", wifiStaNodes.Get(2));
	Names::Add("server", wifiApNode.Get(0));

	NodeContainer wifiStaNodes2;
	wifiStaNodes2.Create(3);
	NodeContainer wifiApNode2;
	wifiApNode2.Add(ring.Get(1));

	Names::Add("client0-vlan2", wifiStaNodes2.Get(0));
	Names::Add("client1-vlan2", wifiStaNodes2.Get(1));
	Names::Add("client2-vlan2", wifiStaNodes2.Get(2));
	Names::Add("server-vlan2", wifiApNode2.Get(0));

	YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
	YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default();
	phy1.SetChannel(channel.Create());
	YansWifiPhyHelper phy2 = YansWifiPhyHelper::Default();
	phy2.SetChannel(channel.Create());

	WifiHelper wifi;
	wifi.SetRemoteStationManager("ns3::AarfWifiManager");

	WifiMacHelper vlan1Mac;
	Ssid ssid = Ssid("vlan1-ssid");
	vlan1Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer staDevices = wifi.Install(phy1, vlan1Mac, wifiStaNodes);
	vlan1Mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
	NetDeviceContainer apDevices = wifi.Install(phy1, vlan1Mac, wifiApNode);

	WifiMacHelper vlan2Mac;
	Ssid ssid2 = Ssid("vlan2-ssid");
	vlan2Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid2),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer staDevices2 = wifi.Install(phy2, vlan2Mac,
			wifiStaNodes2);
	vlan2Mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid2));
	NetDeviceContainer apDevices2 = wifi.Install(phy2, vlan2Mac, wifiApNode2);


	InternetStackHelper stack;
	stack.Install(wifiStaNodes);

	Ipv4AddressHelper address;

	address.SetBase("198.1.1.0", "255.255.255.0");
	address.Assign(staDevices);

	stack.Install(wifiStaNodes2);

	address.SetBase("198.2.2.0", "255.255.255.0");
	address.Assign(staDevices2);



	MobilityHelper mobilityAp;

	mobilityAp.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(40.0), "MinY", DoubleValue(20.0), "DeltaX",
			DoubleValue(10.0), //задает клиентов
			"DeltaY", DoubleValue(3.0), //задает сервер
			"GridWidth", UintegerValue(4), //меняет величину узлов
			"LayoutType", StringValue("RowFirst"));

	mobilityAp.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityAp.Install(wifiApNode);

	MobilityHelper mobilitySta;

	mobilitySta.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(10.0), "MinY", DoubleValue(30.0), "DeltaX",
			DoubleValue(10.0), //задает клиентов
			"DeltaY", DoubleValue(3.0), //задает сервер
			"GridWidth", UintegerValue(4), //меняет величину узлов
			"LayoutType", StringValue("RowFirst"));

	mobilitySta.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilitySta.Install(wifiStaNodes);

	MobilityHelper mobilityAp2;

	mobilityAp2.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(40.0), "MinY", DoubleValue(20.0), "DeltaX",
			DoubleValue(10.0), //задает клиентов
			"DeltaY", DoubleValue(3.0), //задает сервер
			"GridWidth", UintegerValue(4), //меняет величину узлов
			"LayoutType", StringValue("RowFirst"));

	mobilityAp2.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityAp2.Install(wifiApNode2);

	MobilityHelper mobilitySta2;

	mobilitySta2.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(10.0), "MinY", DoubleValue(30.0), "DeltaX",
			DoubleValue(10.0), //задает клиентов
			"DeltaY", DoubleValue(3.0), //задает сервер
			"GridWidth", UintegerValue(4), //меняет величину узлов
			"LayoutType", StringValue("RowFirst"));

	mobilitySta2.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilitySta2.Install(wifiStaNodes2);



	NS_LOG_INFO("Create applications.");

	//------TCP------------//
	//
	// Create a packet sink on the star "hub" to receive packets.
	//
	uint16_t port = 50000;
	//Ipv4AddressHelper address;
	//address.SetBase("10.1.1.0", "255.255.255.0");
	//ring.AssignIpv4Addresses(address);

	//Address hubLocalAddress(InetSocketAddress(Ipv4Address::GetAny(), port));
	//PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory", hubLocalAddress);
	//ApplicationContainer hubApp = packetSinkHelper.Install(star.GetHub());
	//hubApp.Start(Seconds(1.0));
	//hubApp.Stop(Seconds(10.0));

	//
	// Create OnOff applications to send TCP to the hub, one on each spoke node.
	//
	OnOffHelper onOffHelper("ns3::TcpSocketFactory", Address());
	onOffHelper.SetAttribute("OnTime",
			StringValue("ns3::ConstantRandomVariable[Constant=1]"));
	onOffHelper.SetAttribute("OffTime",
			StringValue("ns3::ConstantRandomVariable[Constant=0]"));

	//ApplicationContainer spokeApps;

	//for (uint32_t i = 0; i < star.SpokeCount(); ++i) {
	//	AddressValue remoteAddress(
	//			InetSocketAddress(star.GetHubIpv4Address(i), port));
	//	onOffHelper.SetAttribute("Remote", remoteAddress);
	//	spokeApps.Add(onOffHelper.Install(star.GetSpokeNode(i)));
	//}
	//spokeApps.Start(Seconds(1.0));
	//spokeApps.Stop(Seconds(10.0));

	ApplicationContainer ringNodesApps;
	for (uint32_t i = 0; i < nSpokes; ++i) {
		AddressValue remoteAddress(
				InetSocketAddress(ring.GetIpv4Address(i), port));
		onOffHelper.SetAttribute("Remote", remoteAddress);
		ringNodesApps.Add(onOffHelper.Install(ring.Get(i)));
	}
	ringNodesApps.Start(Seconds(1.0));
	ringNodesApps.Stop(Seconds(10.0));

	//OnOff
	AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper.SetAttribute("Remote", remoteAddress);
	ApplicationContainer p2pApp;
	p2pApp = onOffHelper.Install(ring.Get(1));
	p2pApp.Start(Seconds(1.0));
	p2pApp.Stop(Seconds(10.0));

	NS_LOG_INFO("Enable static global routing.");
	//
	// Turn on global static routing so we can actually be routed across the star.
	//
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	NS_LOG_INFO("Enable pcap tracing.");
	//
	// Do pcap tracing on all point-to-point devices on all nodes.
	pointToPoint.EnablePcapAll("iot");

	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

	//
	uint32_t number_of_nodes = 6;

	CommandLine cmd;
	cmd.Parse(argc, argv);

	PointToPointHelper poinToPointHelper;
	poinToPointHelper.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	poinToPointHelper.SetChannelAttribute("Delay", StringValue("2ms"));
	PointToPointRingHelper ring(number_of_nodes, poinToPointHelper);

	InternetStackHelper internet;
	ring.InstallStack(internet);

	ring.AssignIpv4Addresses(Ipv4AddressHelper("10.1.1.0", "255.255.255.0"));

	//--Node 0--------------------//
	NodeContainer p2pNodes;
	p2pNodes.Add(ring.Get(0));
	p2pNodes.Create(1);
	internet.Install(p2pNodes.Get(1));
	NetDeviceContainer p2pDevices = poinToPointHelper.Install(p2pNodes);

	NodeContainer p2pNodes2;
	p2pNodes2.Add(ring.Get(0));
	p2pNodes2.Create(1);
	internet.Install(p2pNodes2.Get(1));
	NetDeviceContainer p2pDevices2 = poinToPointHelper.Install(p2pNodes2);

	NodeContainer p2pNodes3;
	p2pNodes3.Add(ring.Get(0));
	p2pNodes3.Create(1);
	internet.Install(p2pNodes3.Get(1));
	NetDeviceContainer p2pDevices3 = poinToPointHelper.Install(p2pNodes3);
	//---------------------------//

	//--Node 1--------------------//
	NodeContainer p2pNodesN1_1;
	p2pNodesN1_1.Add(ring.Get(1));
	p2pNodesN1_1.Create(1);
	internet.Install(p2pNodesN1_1.Get(1));
	NetDeviceContainer p2pDevicesN1_1 = poinToPointHelper.Install(p2pNodesN1_1);

	NodeContainer p2pNodesN1_2;
	p2pNodesN1_2.Add(ring.Get(1));
	p2pNodesN1_2.Create(1);
	internet.Install(p2pNodesN1_2.Get(1));
	NetDeviceContainer p2pDevicesN1_2 = poinToPointHelper.Install(p2pNodesN1_2);
	//---------------------------//

	//--Node 2--------------------//
	NodeContainer p2pNodesN2_1;
	p2pNodesN2_1.Add(ring.Get(2));
	p2pNodesN2_1.Create(1);
	internet.Install(p2pNodesN2_1.Get(1));
	NetDeviceContainer p2pDevicesN2_1 = poinToPointHelper.Install(p2pNodesN2_1);

	NodeContainer p2pNodesN2_2;
	p2pNodesN2_2.Add(ring.Get(2));
	p2pNodesN2_2.Create(1);
	internet.Install(p2pNodesN2_2.Get(1));
	NetDeviceContainer p2pDevicesN2_2 = poinToPointHelper.Install(p2pNodesN2_2);
	//---------------------------//

	//--Node 3--------------------//
	NodeContainer p2pNodesN3_1;
	p2pNodesN3_1.Add(ring.Get(3));
	p2pNodesN3_1.Create(1);
	internet.Install(p2pNodesN3_1.Get(1));
	NetDeviceContainer p2pDevicesN3_1 = poinToPointHelper.Install(p2pNodesN3_1);

	NodeContainer p2pNodesN3_2;
	p2pNodesN3_2.Add(ring.Get(3));
	p2pNodesN3_2.Create(1);
	internet.Install(p2pNodesN3_2.Get(1));
	NetDeviceContainer p2pDevicesN3_2 = poinToPointHelper.Install(p2pNodesN3_2);

	NodeContainer p2pNodesN3_3;
	p2pNodesN3_3.Add(ring.Get(3));
	p2pNodesN3_3.Create(1);
	internet.Install(p2pNodesN3_3.Get(1));
	NetDeviceContainer p2pDevicesN3_3 = poinToPointHelper.Install(p2pNodesN3_3);
	//---------------------------//

	//--Node 4--------------------//
	NodeContainer p2pNodesN4_1;
	p2pNodesN4_1.Add(ring.Get(4));
	p2pNodesN4_1.Create(1);
	internet.Install(p2pNodesN4_1.Get(1));
	NetDeviceContainer p2pDevicesN4_1 = poinToPointHelper.Install(p2pNodesN4_1);

	NodeContainer p2pNodesN4_2;
	p2pNodesN4_2.Add(ring.Get(4));
	p2pNodesN4_2.Create(1);
	internet.Install(p2pNodesN4_2.Get(1));
	NetDeviceContainer p2pDevicesN4_2 = poinToPointHelper.Install(p2pNodesN4_2);

	NodeContainer p2pNodesN4_3;
	p2pNodesN4_3.Add(ring.Get(4));
	p2pNodesN4_3.Create(1);
	internet.Install(p2pNodesN4_3.Get(1));
	NetDeviceContainer p2pDevicesN4_3 = poinToPointHelper.Install(p2pNodesN4_3);
	//---------------------------//

	//--Node 5--------------------//
	NodeContainer p2pNodesN5_1;
	p2pNodesN5_1.Add(ring.Get(5));
	p2pNodesN5_1.Create(1);
	internet.Install(p2pNodesN5_1.Get(1));
	NetDeviceContainer p2pDevicesN5_1 = poinToPointHelper.Install(p2pNodesN5_1);

	NodeContainer p2pNodesN5_2;
	p2pNodesN5_2.Add(ring.Get(5));
	p2pNodesN5_2.Create(1);
	internet.Install(p2pNodesN5_2.Get(1));
	NetDeviceContainer p2pDevicesN5_2 = poinToPointHelper.Install(p2pNodesN5_2);
	//---------------------------//

	//address.Assign(p2pDevices);

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

	ApplicationContainer ringNodesApps;
	for (uint32_t i = 0; i < number_of_nodes; i++) {
		AddressValue remoteAddress(
				InetSocketAddress(ring.GetIpv4Address(i), port));
		onOffHelper.SetAttribute("Remote", remoteAddress);
		ringNodesApps.Add(onOffHelper.Install(ring.Get(i)));
	}
	ringNodesApps.Start(Seconds(1.0));
	ringNodesApps.Stop(Seconds(10.0));

	AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper.SetAttribute("Remote", remoteAddress);
	ApplicationContainer p2pApp;
	p2pApp = onOffHelper.Install(p2pNodes.Get(1));
	p2pApp.Start(Seconds(1.0));
	p2pApp.Stop(Seconds(10.0));

	AddressValue remoteAddress2(
			InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper.SetAttribute("Remote", remoteAddress2);
	ApplicationContainer p2pApp2;
	p2pApp2 = onOffHelper.Install(p2pNodes2.Get(1));
	p2pApp2.Start(Seconds(1.0));
	p2pApp2.Stop(Seconds(10.0));

	AddressValue remoteAddress3(
			InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper.SetAttribute("Remote", remoteAddress3);
	ApplicationContainer p2pApp3;
	p2pApp3 = onOffHelper.Install(p2pNodes3.Get(1));
	p2pApp3.Start(Seconds(1.0));
	p2pApp3.Stop(Seconds(10.0));

	AddressValue remoteAddressN1_1(
			InetSocketAddress(ring.GetIpv4Address(1), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN1_1);
	ApplicationContainer p2pAppN1_1;
	p2pAppN1_1 = onOffHelper.Install(p2pNodesN1_1.Get(1));
	p2pAppN1_1.Start(Seconds(1.0));
	p2pAppN1_1.Stop(Seconds(10.0));

	AddressValue remoteAddressN1_2(
			InetSocketAddress(ring.GetIpv4Address(2), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN1_2);
	ApplicationContainer p2pAppN1_2;
	p2pAppN1_2 = onOffHelper.Install(p2pNodesN1_2.Get(1));
	p2pAppN1_2.Start(Seconds(1.0));
	p2pAppN1_2.Stop(Seconds(10.0));

	AddressValue remoteAddressN2_1(
			InetSocketAddress(ring.GetIpv4Address(2), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN1_1);
	ApplicationContainer p2pAppN2_1;
	p2pAppN2_1 = onOffHelper.Install(p2pNodesN2_1.Get(1));
	p2pAppN2_1.Start(Seconds(1.0));
	p2pAppN2_1.Stop(Seconds(10.0));

	AddressValue remoteAddressN2_2(
			InetSocketAddress(ring.GetIpv4Address(2), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN2_2);
	ApplicationContainer p2pAppN2_2;
	p2pAppN2_2 = onOffHelper.Install(p2pNodesN2_1.Get(1));
	p2pAppN2_2.Start(Seconds(1.0));
	p2pAppN2_2.Stop(Seconds(10.0));

	AddressValue remoteAddressN3_1(
			InetSocketAddress(ring.GetIpv4Address(3), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN3_1);
	ApplicationContainer p2pAppN3_1;
	p2pAppN3_1 = onOffHelper.Install(p2pNodesN3_1.Get(1));
	p2pAppN3_1.Start(Seconds(1.0));
	p2pAppN3_1.Stop(Seconds(10.0));

	AddressValue remoteAddressN3_2(
			InetSocketAddress(ring.GetIpv4Address(3), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN3_2);
	ApplicationContainer p2pAppN3_2;
	p2pAppN3_2 = onOffHelper.Install(p2pNodesN3_2.Get(1));
	p2pAppN3_2.Start(Seconds(1.0));
	p2pAppN3_2.Stop(Seconds(10.0));

	AddressValue remoteAddressN3_3(
			InetSocketAddress(ring.GetIpv4Address(3), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN3_3);
	ApplicationContainer p2pAppN3_3;
	p2pAppN3_3 = onOffHelper.Install(p2pNodesN3_3.Get(1));
	p2pAppN3_3.Start(Seconds(1.0));
	p2pAppN3_3.Stop(Seconds(10.0));

	AddressValue remoteAddressN4_1(
			InetSocketAddress(ring.GetIpv4Address(4), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN4_1);
	ApplicationContainer p2pAppN4_1;
	p2pAppN4_1 = onOffHelper.Install(p2pNodesN4_1.Get(1));
	p2pAppN4_1.Start(Seconds(1.0));
	p2pAppN4_1.Stop(Seconds(10.0));

	AddressValue remoteAddressN4_2(
			InetSocketAddress(ring.GetIpv4Address(4), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN4_2);
	ApplicationContainer p2pAppN4_2;
	p2pAppN4_2 = onOffHelper.Install(p2pNodesN4_2.Get(1));
	p2pAppN4_2.Start(Seconds(1.0));
	p2pAppN4_2.Stop(Seconds(10.0));

	AddressValue remoteAddressN4_3(
			InetSocketAddress(ring.GetIpv4Address(4), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN4_3);
	ApplicationContainer p2pAppN4_3;
	p2pAppN4_3 = onOffHelper.Install(p2pNodesN4_3.Get(1));
	p2pAppN4_3.Start(Seconds(1.0));
	p2pAppN4_3.Stop(Seconds(10.0));

	AddressValue remoteAddressN5_1(
			InetSocketAddress(ring.GetIpv4Address(5), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN5_1);
	ApplicationContainer p2pAppN5_1;
	p2pAppN5_1 = onOffHelper.Install(p2pNodesN5_1.Get(1));
	p2pAppN5_1.Start(Seconds(1.0));
	p2pAppN5_1.Stop(Seconds(10.0));

	AddressValue remoteAddressN5_2(
			InetSocketAddress(ring.GetIpv4Address(5), port));
	onOffHelper.SetAttribute("Remote", remoteAddressN5_2);
	ApplicationContainer p2pAppN5_2;
	p2pAppN5_2 = onOffHelper.Install(p2pNodesN5_2.Get(1));
	p2pAppN5_2.Start(Seconds(1.0));
	p2pAppN5_2.Stop(Seconds(10.0));

	NS_LOG_INFO("Enable static global routing.");
	// Turn on glbal static routing so we can actually be routed across the ring.//
	//Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	NS_LOG_INFO("Enable pcap tracing.");
	// Do pcap tracing on all point-to-point devices on all nodes.
	//pointToPoint.EnablePcapAll("star");

	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}


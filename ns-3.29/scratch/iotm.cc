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

	/* Create a ring */
	PointToPointHelper poinToPointHelper;
	poinToPointHelper.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	poinToPointHelper.SetChannelAttribute("Delay", StringValue("2ms"));
	PointToPointRingHelper ring(number_of_nodes, poinToPointHelper);

	InternetStackHelper internet;
	ring.InstallStack(internet);
	ring.AssignIpv4Addresses(Ipv4AddressHelper("194.228.0.0", "255.255.255.0"));

	//--Node 0--------------------//
	NodeContainer n;
	n.Create(3);

	NodeContainer twoNodesContainer;
	twoNodesContainer.Add(ring.Get(0));
	twoNodesContainer.Add(n.Get(0));

	internet.Install(twoNodesContainer.Get(1));
	Ipv4AddressHelper ipv4;
	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer ipv4ContainerFor_p2pNodes = ipv4.Assign (poinToPointHelper.Install(twoNodesContainer));

	/*
	NodeContainer p2pNodesContainer2;
	p2pNodesContainer2.Add(twoNodesContainer.Get(0));
	p2pNodesContainer2.Add(n.Get(1));

	NodeContainer p2pNodesContainer3;
	p2pNodesContainer3.Add(twoNodesContainer.Get(0));
	p2pNodesContainer3.Add(n.Get(2));
*/


	//internet.Install(p2pNodesContainer2.Get(1));
	//internet.Install(p2pNodesContainer3.Get(1));



	//Ipv4InterfaceContainer ipv4ContainerFor_p2pNodes2 = ipv4.Assign (poinToPointHelper.Install(p2pNodesContainer2));
	//Ipv4InterfaceContainer ipv4ContainerFor_p2pNodes3 = ipv4.Assign (poinToPointHelper.Install(p2pNodesContainer3));
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

	  // Create router nodes, initialize routing database and set up the routing
	  // tables in the nodes.
	  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();



	  NS_LOG_INFO ("Create Applications.");
	  uint16_t port = 9;   // Discard port (RFC 863)
	  OnOffHelper onoff ("ns3::TcpSocketFactory",
	                     Address (InetSocketAddress (ring.GetIpv4Address(0), port)));
	  onoff.SetConstantRate (DataRate ("448kb/s"));
	  ApplicationContainer apps = onoff.Install (ring.Get (0));
	  apps.Start (Seconds (1.0));
	  apps.Stop (Seconds (10.0));

	  // Create a packet sink to receive these packets
	  PacketSinkHelper sink ("ns3::TcpSocketFactory",
	                         Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
	  apps = sink.Install (twoNodesContainer.Get (1));
	  apps.Start (Seconds (1.0));
	  apps.Stop (Seconds (10.0));

	/*
	  // Create a similar flow from n3 to n1, starting at time 1.1 seconds
	  onoff.SetAttribute ("Remote",
	                      AddressValue (InetSocketAddress (i1i2.GetAddress (0), port)));
	  apps = onoff.Install (c.Get (3));
	  apps.Start (Seconds (1.1));
	  apps.Stop (Seconds (10.0));

	  // Create a packet sink to receive these packets
	  apps = sink.Install (c.Get (1));
	  apps.Start (Seconds (1.1));
	  apps.Stop (Seconds (10.0));
  */





/*
	uint16_t port = 50000;

	OnOffHelper onOffHelper("ns3::TcpSocketFactory", Address());


	ApplicationContainer ringNodesApps;
	for (uint32_t i = 0; i < number_of_nodes-1; i++) {
			AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(i), port));
			onOffHelper.SetAttribute("Remote", remoteAddress);
			ringNodesApps.Add(onOffHelper.Install(ring.Get(i+1)));
	}
	AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(0), port));
			onOffHelper.SetAttribute("Remote", remoteAddress);
    ringNodesApps.Add(onOffHelper.Install(ring.Get(number_of_nodes-1)));
	//  onoff.SetConstantRate (DataRate ("448kb/s"));
	ringNodesApps.Start(Seconds(1.0));
	ringNodesApps.Stop(Seconds(10.0));
*/

	  // Create the OnOff application to send UDP datagrams of size
	  // 210 bytes at a rate of 448 Kb/s
	//  NS_LOG_INFO ("Create Applications.");
	//  uint16_t port = 9;   // Discard port (RFC 863)
	//  OnOffHelper onoff ("ns3::UdpSocketFactory",
	//                     Address (InetSocketAddress (i3i2.GetAddress (0), port)));
	//  onoff.SetConstantRate (DataRate ("448kb/s"));
	//  ApplicationContainer apps = onoff.Install (c.Get (0));
	 // apps.Start (Seconds (1.0));
	 // apps.Stop (Seconds (10.0));



/*
	OnOffHelper onOffHelper2("ns3::TcpSocketFactory", Address());
		onOffHelper2.SetAttribute("OnTime",
				StringValue("ns3::ConstantRandomVariable[Constant=1]"));
		onOffHelper2.SetAttribute("OffTime",
				StringValue("ns3::ConstantRandomVariable[Constant=0]"));


	AddressValue remoteAddress2(
			InetSocketAddress(ring.GetIpv4Address(0), port));
	onOffHelper2.SetAttribute("Remote", remoteAddress2);
	ApplicationContainer p2pApp;
	p2pApp = onOffHelper2.Install(p2pNodes.Get(1));
	p2pApp.Start(Seconds(1.0));
	p2pApp.Stop(Seconds(10.0));


	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

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
*/



	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}


/*
 * ring.cc
 *
 *  Created on: Dec 13, 2018
 *      Author: lika
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-net-device.h"
#include "ns3/wifi-phy.h"
#include "wifi-80211p-helper.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

	CommandLine cmd;
	cmd.Parse(argc, argv);

	/**
	 * Создаем кольцо
	 */

	//Создадим три пустых узла
	NodeContainer ringNodes;
	ringNodes.Create(3);

	//Они будут составлять одну локальную сеть, но также служить
	//шлюзами в локальные подсети интернет вещей
	Names::Add("Gate0", ringNodes.Get(0));
	Names::Add("Gate1", ringNodes.Get(1));
	Names::Add("Gate2", ringNodes.Get(2));

	//Установим их в нужные позиции
	MobilityHelper mobility;
	mobility.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(30.0), "MinY", DoubleValue(-10.0));
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(ringNodes.Get(0));

	MobilityHelper mobility2;
	mobility2.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(15.0), "MinY", DoubleValue(10.0));
	mobility2.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility2.Install(ringNodes.Get(1));

	MobilityHelper mobility3;
	mobility3.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(45.0), "MinY", DoubleValue(10.0));
	mobility3.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility3.Install(ringNodes.Get(2));

	/**
	 * Создадим их собественную локальную сеть
	 */
	YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
	YansWifiPhyHelper ringPhy = YansWifiPhyHelper::Default();

	ringPhy.SetChannel(channel.Create());



	//После того как уровень PHY настроен, перейдём к настройке уровня MAC
	//в беспроводных сетях
	/**
	 * Helps to create wifi 802.11p objects of WifiNetDevice class.
	 * This class can help to create a large set of similar wifi
	 * 802.11p objects and to configure a large set of their attributes
	 * during creation.
	 */
	Wifi80211pHelper  wifi;
	wifi.SetRemoteStationManager("ns3::RegularWifiMac");

	//Следующий фрагмент кода обеспечивает моделирование wi-fi устройств и
	//канала связи между ними.
	//Настройка PHY уровня и канала связи
	WifiMacHelper ringMac;
	Ssid ringSsid = Ssid("ring-ssid");
	ringMac.SetType("ns3::RegularWifiMac", "Ssid", SsidValue(ringSsid),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer ringDevices = wifi.Install(ringPhy, ringMac, ringNodes);



	 WifiNetDevice wifiRingDevices;
	wifiRingDevices.SetNode(ringNodes.Get(0));
	wifiRingDevices.SetNode(ringNodes.Get(1));
	wifiRingDevices.SetNode(ringNodes.Get(2));





	//Create two wi-fi networks with adjacent bus nodes:
	NodeContainer vlan1Nodes;
	vlan1Nodes.Create(2);
	NodeContainer gate;
	gate.Add(ringNodes.Get(0));

	/**
	 * NodeContainer - special container for nodes
	 * There can be one or two nodes (in this case there will
	 * be a connection between nodes)
	 * Simply put, it creates node from nothing, like putting a dot
	 */
	NodeContainer vlan2Nodes;
	vlan2Nodes.Create(2);
	NodeContainer gate2;
	gate2.Add(ringNodes.Get(2));


	YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default();
	phy1.SetChannel(channel.Create());
	YansWifiPhyHelper phy2 = YansWifiPhyHelper::Default();
	phy2.SetChannel(channel.Create());

	//Данный код создаёт сервис 802.11, устанавливает
	//его тип равным «ns3 :: StaWifiMac», SSID равным «ns-3-ssid»
	// и значение атрибута
	//ActiveProbing (активировать зондирование) с типом «false».
	WifiMacHelper vlan1Mac;
	Ssid ssid = Ssid("vlan1-ssid");
	vlan1Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer vlan1Devices = wifi.Install(phy1, vlan1Mac, vlan1Nodes);
	vlan1Mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
	NetDeviceContainer vlan1ApDevice = wifi.Install(phy1, vlan1Mac, gate);

	WifiMacHelper vlan2Mac;
	Ssid ssid2 = Ssid("vlan2-ssid");
	vlan2Mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid2),
			"ActiveProbing", BooleanValue(false));
	NetDeviceContainer vlan2Devices = wifi.Install(phy2, vlan2Mac, vlan2Nodes);
	vlan2Mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid2));
	NetDeviceContainer vlan2ApDevice = wifi.Install(phy2, vlan2Mac, gate2);


	MobilityHelper vlan1Node0;
	vlan1Node0.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(0.0), "MinY", DoubleValue(0.0));
	vlan1Node0.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	vlan1Node0.Install(vlan1Nodes.Get(0));

	MobilityHelper vlan1Node1;
	vlan1Node1.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
				DoubleValue(0.0), "MinY", DoubleValue(0.0));
	vlan1Node1.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	vlan1Node1.Install(vlan1Nodes.Get(1));


	MobilityHelper vlan2Node0;
	vlan2Node0.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(60.0), "MinY", DoubleValue(10.0));
	vlan2Node0.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	vlan2Node0.Install(vlan2Nodes.Get(0));

	MobilityHelper vlan2Node1;
	vlan2Node1.SetPositionAllocator("ns3::GridPositionAllocator", "MinX",
			DoubleValue(60.0), "MinY", DoubleValue(0.0));
	vlan2Node1.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	vlan2Node1.Install(vlan2Nodes.Get(1));



	/**
	 * Настраиваем уровень приложения для всех
	 */

	InternetStackHelper stack;

	stack.Install(vlan1Nodes);
	stack.Install(vlan2Nodes);
	stack.Install(ringNodes);

	Ipv4AddressHelper addressIpv4;

	//Address address("10.1.1.0", "255.255.255.0");
	//wifiRingDevices.SetAddress(address);

	//Ipv4InterfaceContainer ringGate0Dev;
	//ringGate0Dev = addressIpv4.Assign(wifiRingDevices.Get(0));

	addressIpv4.SetBase("10.5.2.0", "255.255.255.0");
	addressIpv4.Assign(vlan1Devices);
	addressIpv4.Assign(vlan1ApDevice);

	addressIpv4.SetBase("10.4.3.0", "255.255.255.0");
	addressIpv4.Assign(vlan2Devices);
	Ipv4InterfaceContainer apDev;
	apDev = addressIpv4.Assign(vlan2ApDevice);


	/**
	 * Настраиваем сообщение между узлами кольца
	 */
	/*
	UdpEchoServerHelper echoServer(9);
	ApplicationContainer serverApp = echoServer.Install(ringNodes.Get(0));
	serverApp.Start(Seconds(1.0));
	serverApp.Stop(Seconds(20.0));

	UdpEchoClientHelper echoClient(ringGate0Dev.GetAddress(0), 9);
	echoClient.SetAttribute("MaxPackets", UintegerValue(5));
	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize", UintegerValue(1024));
*/
	/*
	ApplicationContainer ringClientApp = echoClient.Install(ringNodes.Get(2));
	ringClientApp.Start(Seconds(2.0));
	ringClientApp.Stop(Seconds(20.0));

	UdpEchoServerHelper echoServer1(9);
	ApplicationContainer serverApp1 = echoServer.Install(ringNodes.Get(2));
	serverApp1.Start(Seconds(1.0));
	serverApp1.Stop(Seconds(20.0));

	UdpEchoClientHelper echoClient1(apDev.GetAddress(0), 9);
	echoClient1.SetAttribute("MaxPackets", UintegerValue(5));
	echoClient1.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	echoClient1.SetAttribute("PacketSize", UintegerValue(1024));

	ApplicationContainer ringClientApp2 = echoClient.Install(ringNodes.Get(1));
	ringClientApp2.Start(Seconds(2.0));
	ringClientApp2.Stop(Seconds(20.0));
*/
	/*
	 ApplicationContainer clientApp1 = echoClient.Install(vlan1Nodes.Get(0));
	 clientApp1.Start(Seconds(2.0));
	 clientApp1.Stop(Seconds(10.0));

	 ApplicationContainer clientApp2 = echoClient.Install(vlan2Nodes.Get(0));
	 clientApp2.Start(Seconds(2.0));
	 clientApp2.Stop(Seconds(10.0));
	 */

	//????
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	Simulator::Stop(Seconds(10.0));

	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();

}

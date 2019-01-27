/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 MIRKO BANCHI
 *
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
 *
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */
#ifndef NQOS_WIFI_MAC_HELPER_H
#define NQOS_WIFI_MAC_HELPER_H

#include "wifi-helper.h"

namespace ns3 {

class NqosWifiMacHelper: public WifiMacHelper {
public:
	NqosWifiMacHelper();

	virtual ~NqosWifiMacHelper();
	static NqosWifiMacHelper Default(void);
	void SetType(std::string type, std::string n0 = "",
			const AttributeValue &v0 = EmptyAttributeValue(), std::string n1 =
					"", const AttributeValue &v1 = EmptyAttributeValue(),
			std::string n2 = "", const AttributeValue &v2 =
					EmptyAttributeValue(), std::string n3 = "",
			const AttributeValue &v3 = EmptyAttributeValue(), std::string n4 =
					"", const AttributeValue &v4 = EmptyAttributeValue(),
			std::string n5 = "", const AttributeValue &v5 =
					EmptyAttributeValue(), std::string n6 = "",
			const AttributeValue &v6 = EmptyAttributeValue(), std::string n7 =
					"", const AttributeValue &v7 = EmptyAttributeValue());
private:
	virtual Ptr<WifiMac> Create(void) const;

	ObjectFactory m_mac;
};

} // namespace ns3

#endif /* NQOS_WIFI_MAC_HELPER_H */


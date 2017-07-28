#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>


using namespace boost::property_tree;

class RXInfo
{
public:
	unsigned long freq() {return _frequency;}
	void freq(unsigned long frequency) {_frequency = frequency;}

	static RXInfo decode(ptree pt) {
		RXInfo rxinfo;

		rxinfo.freq( pt.get_optional<unsigned long>("freq").get() );

		return rxinfo;
	}
private:
	unsigned long _frequency;
};


class RXPK
{
public:
	RXInfo operator[](unsigned int num) {return _rxinfos[num];}
	void add(RXInfo rxinfo) {_rxinfos.push_back(rxinfo);}

	static RXPK decode(ptree::value_type& rxinfos) {
		BOOST_FOREACH(ptree::value_type& rxinfo, rxinfos) {
			RXInfo rxinfo = RXInfo::decode(rxinfo);
			_rxinfos.push_back(rxinfo);
		}
	}
private:
	std::vector<RXInfo> _rxinfos;
};


class JSONPayload
{
public:
	void rxpk(RXPK r) { _rxpk = r; }
	RXPK rxpk() { return _rxpk; }

	static JSONPayload decode(std::string json_string) {
		JSONPayload json_payload;

		std::stringstream ss(json_string);
		ptree pt;
		read_json(ss, pt);

		ptree::value_type& child = pt.get_child("rxpk")
		rxpk(RXPK::decode(child));
		
		return rxpk;
	}
private:
	RXPK _rxpk;
};


using namespace std;
int main()
{

	cout << rxinfo.freq() << endl;

	return 0;
}

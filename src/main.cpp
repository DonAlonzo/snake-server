#include "main.hpp"

using websocketpp::connection_hdl;
typedef std::map<connection_hdl, PlayerData, std::owner_less<connection_hdl>> con_list;
typedef websocketpp::server<websocketpp::config::asio> server;

struct PlayerData {
	int sessionid;
	std::string name;
};

class SnakeServer {
public:
	SnakeServer() {
		m_server.init_asio();

		m_server.set_open_handler(websocketpp::lib::bind(&SnakeServer::on_open, this, websocketpp::lib::placeholders::_1));
		m_server.set_close_handler(websocketpp::lib::bind(&SnakeServer::on_close, this, websocketpp::lib::placeholders::_1));
		m_server.set_message_handler(websocketpp::lib::bind(&SnakeServer::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
	}

	void broadcast(std::string payload) {
		for (auto& it : m_connections) {
			m_server.send(it.first, payload, websocketpp::frame::opcode::text);
		}
	}

	void on_open(connection_hdl hdl) {
		PlayerData data;
		data.sessionid = m_next_sessionid++;
		data.name = "unknown";

		m_connections[hdl] = data;

		broadcast(std::to_string(m_connections.size()));
	}

	void on_close(connection_hdl hdl) {
		m_connections.erase(hdl);

		broadcast(std::to_string(m_connections.size()));
	}

	void on_message(connection_hdl hdl, server::message_ptr msg) {
		auto data = get_data(hdl);

		broadcast(msg->get_payload());
		std::cout << msg->get_payload() << std::endl;
	}

	PlayerData& get_data(connection_hdl hdl) {
		auto it = m_connections.find(hdl);
		if (it == m_connections.end()) {
			throw std::invalid_argument("No data avaliable for session");
		}
		return it->second;
	}

	void run(uint16_t port) {
		m_server.listen(port);
		m_server.start_accept();
		std::cout << "Server running on port " << std::to_string(port) << std::endl;
		m_server.run();
	}

private:
	con_list m_connections;
	server m_server;
	int m_next_sessionid;
};

int main() {
	SnakeServer server;
	server.run(9002);
}
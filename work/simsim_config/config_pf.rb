log 'Simsim'

require_relative '/home/ta_kondoh/work/device_gw_simulator/lib/packet_forwarder/protocol'
#require_relative '/home/ta_kondoh/work/device_gw_simulator/lib/lora/protocol'
#Lora = PHYPayload

require_relative '/home/ta_kondoh/work/simsim/protocol/raw'
require 'base64'
class String
  def encode64
    Base64.encode64(self)
  end
  def decode64
    Base64.decode64(self)
  end
end

peer '127.0.0.1:1701', '127.0.0.1:1700', PacketForwarder
peer :lorasim, '127.0.0.1:50001', '127.0.0.1:50000', Raw


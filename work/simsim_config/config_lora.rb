log 'Simsim'

require_relative '/home/ta_kondoh/work/device_gw_simulator/lib/lora/protocol'
Lora = PHYPayload

peer '127.0.0.1:50000', '127.0.0.1:50001', Lora


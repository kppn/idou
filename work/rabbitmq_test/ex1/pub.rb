#!/usr/bin/env ruby
# encoding: utf-8

require "bunny"


conn = Bunny.new(:hostname => "127.0.0.1")
conn.start

ch = conn.create_channel

q = ch.queue("hello")
ch.default_exchange.publish("Hello World!", :routing_key => q.name)
puts "[x]sent 'Hello World!'"

conn.close




#!/usr/bin/env ruby
# encoding: utf-8

require "bunny"

conn = Bunny.new
conn.start

ch = conn.create_channel
q = ch.queue("hello")

p q
p q.class.ancestors
p q.channel
p q.channel.class.ancestors
p q.channel.connection
p q.channel.connection.class.ancestors
p q.channel.connection.instance_variables

q.subscribe(:manual_ack => true, :block => true) do |delivery_info, properties, body|
  puts " [x] Received #{body}"
  # imitate some work
  sleep body.count(".").to_i
  puts " [x] Done"

  ch.ack(delivery_info.delivery_tag)
end

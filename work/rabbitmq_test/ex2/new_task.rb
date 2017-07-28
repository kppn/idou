#!/usr/bin/env ruby
# encoding: utf-8

require "bunny"


conn = Bunny.new(:hostname => "127.0.0.1")
conn.start
ch = conn.create_channel
q = ch.queue("hello")

msg  = ARGV.empty? ? "Hello World!" : ARGV.join(" ")

q.publish(msg, :persistent => true)
puts " [x] Sent #{msg}"


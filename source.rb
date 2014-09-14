require 'base64'
class Producer
  def each
    @enum ||= Enumerator.new do |y|
      10.times do |t|
        y.yield "#{t*2} / #{Base64.encode64(t.to_s)}"
      end
    end
    @enum.next
  end
end
Producer

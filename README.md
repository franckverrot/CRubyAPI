# CRuby API

# RATIONALE

Sample C application that:

1. Boots a Ruby VM
2. Loads code from a Ruby source file (named "source.rb")
3. Initializes an new object whose class is the latest one returned by that Ruby source file
4. Iterates over that object's `each` method

# EXAMPLE

Just type `make`. But given:

1. The source file is:

```ruby
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
```

2. You start the compiled file manually

It will give you:

    λ ./embed_ruby
    0 / MA==

    2 / MQ==

    4 / Mg==

    6 / Mw==

    8 / NA==

    10 / NQ==

    12 / Ng==

    14 / Nw==

    16 / OA==

    18 / OQ==

# LESSONS LEARNED

* rb_protect: Protect C code from segfaults and other things that could go really wrong
* rb_funcallv_public: If not really thought through, your code will use the functions that can call private/protected methods, and this is bad
* rb_class_new_instance: Does the alloc+init of a new object, pretty much all you'll ever need

# LICENSE

GPLv3. Copyright 2014 - Franck Verrot.

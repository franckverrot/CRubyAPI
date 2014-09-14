all:
	gcc -o embed_ruby -I ~/.rubies/ruby-2.1.0/include/ruby-2.1.0 -I ~/.rubies/ruby-2.1.0/include/ruby-2.1.0/x86_64-darwin13.0/ -L ~/.rubies/ruby-2.1.0/lib/ -lruby-static -framework CoreFoundation -g embed_ruby.c
	./embed_ruby

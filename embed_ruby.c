#include <ruby.h>

VALUE each();
char *load_file_in_str(const char *in);

int main()
{
    const char * options[] = { "", "-enil", 0 };
    int result;
    char *iterator_code;

    ruby_init();
    ruby_init_loadpath();
    ruby_exec_node(ruby_options(2, (char**)options));

    iterator_code = load_file_in_str("source.rb");

    VALUE class = rb_eval_string_protect(iterator_code, &result);
    if (result) {
      perror("Can't eval the iterator :\n");
      return 1;
    }
    fprintf(stderr, "Source code loaded\n");

    VALUE iterator = rb_class_new_instance(0, NULL, class);
    if (result) {
      perror("Can't initialize the iterator :\n");
      return 1;
    }

    fprintf(stderr, "Iterator class initialized\n");

    for(VALUE output;;) {
      output = rb_protect(each, iterator, &result);
      if (result) {
        if(Qnil == output) {
          /* No result, let's just stop here */
          break;
        } else {
          perror("Error :");
          return 1;
        }
      } else {
        fprintf(stdout, "%s\n", RSTRING_PTR(output));
      }
    }

    free(iterator_code);
    ruby_cleanup(0);
    return 0;
}

char *load_file_in_str(const char *in) {
  FILE *f = fopen(in, "r");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char * out = malloc(fsize + 1);
  fread(out, fsize, 1, f);
  fclose(f);

  out[fsize] = 0;
  return out;
}

VALUE each(VALUE iterator) {
  VALUE output = rb_funcallv_public(iterator, rb_intern("each"), 0, NULL);
  return output;
}

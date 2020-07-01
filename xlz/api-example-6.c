#include "jerryscript.h"
#include "jerryscript-ext/handler.h"

int main (void) {
  const jerry_char_t script[] = "var person = {firstName:\"Bill\", lastName:\"Gates\", age:62, eyeColor:\"blue\"}; \n \
				print ('Hello o from world!');\n \
				var person2 = {firstName:\"Bzill\", lastName:\"Gzates\", age:12, eyeColor:\"blue\"}; \n \
        var person3 = {firstName:\"zill\", lastName:\"ates\", age:12, eyeColor:\"red\"}; \n \
				person[\"lastName\"] = \"zhang\";	\n \
				person[\"firstName\"] = \"long\";	\n \
				person2[\"lastName\"];\n \
				person[\"foo\"] = function (a, b) {return a * b}; \n \
				person2.foo(1,2); \n \
				";
				
  const jerry_length_t script_size = sizeof (script) - 1;

  /* Initialize engine */
  jerry_init (JERRY_INIT_SHOW_OPCODES);
  //jerry_init (JERRY_INIT_SHOW_REGEXP_OPCODES);
 
  /* Register 'print' function from the extensions to the global object */
  jerryx_handler_register_global ((const jerry_char_t *) "print",
                                  jerryx_handler_print);

  /* Setup Global scope code */
  jerry_value_t parsed_code = jerry_parse (NULL, 0, script, script_size, JERRY_PARSE_NO_OPTS);

  if (!jerry_value_is_error (parsed_code)) {
    /* Execute the parsed source code in the Global scope */
    jerry_value_t ret_value = jerry_run (parsed_code);

    /* Returned value must be freed */
    jerry_release_value (ret_value);
  }

  /* Parsed source code must be freed */
  jerry_release_value (parsed_code);

  /* Cleanup engine */
  jerry_cleanup ();

  return 0;
}

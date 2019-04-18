#ifndef JSRUNNER_
#define JSRUNNER_
#include <duktape.h>
class JsRunner {
public:
	JsRunner();
	~JsRunner();
	void run();
	void test_duk_alloc();
	void test_duk_base64();
	void test_duk_free();
	void PRINT_DUK_STACK();
	void test_duk_compile();
private:
	duk_context *ctx;
};

#endif // !JSRUNNER_

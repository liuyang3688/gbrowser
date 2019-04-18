#include "jsrunner.h"
#include <string>
#include <filesystem>
namespace fs = std::experimental::filesystem;

JsRunner::JsRunner() {
	ctx = duk_create_heap_default();
	if (ctx == NULL) {
		//throw 
	}
}
JsRunner::~JsRunner() {
	if (ctx) {
		duk_destroy_heap(ctx);
	}
}
void JsRunner::run() {
	//test_duk_alloc();
	//test_duk_base64();
	test_duk_compile();
	test_duk_free();
}
void JsRunner::test_duk_compile() {
	fs::path jsPath = "./js/func.js";

	//// 读取js脚本内容
	//std::string script = readFileString(path);
	//// 放入栈顶
	//duk_push_string(ctx, script.c_str());
	//duk_push_string(ctx, "(function(exports, require, module, __filename, __dirname){");
	//const char* src = duk_require_string(ctx, -2);
	//duk_push_string(ctx, (src[0] == '#' && src[1] == '!') ? '//', "");
	//duk_dup(ctx, -3);
	//duk_push_string(ctx, "\n})");
	//duk_concat(ctx, 4);
	//duk_push_string(ctx, filename);
	////[source filename] -> [function]
	//duk_compile(ctx, DUK_COMPILE_EVAL | DUK_COMPILE_STRICT);

}
void JsRunner::test_duk_alloc() {

	//void* buf = duk_alloc(ctx, 1024);
	void* buf = duk_alloc_raw(ctx, 1024);

	if (buf) {
		printf("内存分配成功，%p", buf);
	}
	else {
		printf("内存分配失败");
	}
}
void JsRunner::test_duk_base64() {
	duk_push_string(ctx, "liuyang");
	PRINT_DUK_STACK();
	duk_base64_encode(ctx, -1);  /* buffer */
	PRINT_DUK_STACK();
	duk_base64_decode(ctx, -1);
	PRINT_DUK_STACK();
	duk_buffer_to_string(ctx, -1);
	PRINT_DUK_STACK();
	duk_pop(ctx);
}
void JsRunner::test_duk_free() {

}
void JsRunner::PRINT_DUK_STACK() {
	duk_push_context_dump(ctx);
	printf("===========当前栈===========\n");
	printf("%s\n", duk_to_string(ctx, -1));
	duk_pop(ctx);
}
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x885b74e3, "module_layout" },
	{ 0xd29a78e, "tty_unregister_driver" },
	{ 0x65bc8a91, "tty_unregister_device" },
	{ 0xf901fbc0, "tty_register_driver" },
	{ 0x881c0687, "tty_set_operations" },
	{ 0x67b27ec1, "tty_std_termios" },
	{ 0x4f80e6be, "alloc_tty_driver" },
	{ 0x1882f511, "tty_wakeup" },
	{ 0x350a786c, "tty_flip_buffer_push" },
	{ 0x8384a2c5, "tty_unlock" },
	{ 0x52da18c1, "tty_insert_flip_string_fixed_flag" },
	{ 0x25ec1b28, "strlen" },
	{ 0xed302f0f, "tty_lock" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "BC8921CD301828E4CC95DD2");

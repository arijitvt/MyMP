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
	{ 0x68d372d2, "module_layout" },
	{ 0xb3bfe835, "tty_unregister_driver" },
	{ 0x111cbdec, "tty_unregister_device" },
	{ 0xa4c0b6e4, "tty_register_driver" },
	{ 0x93fbf589, "tty_set_operations" },
	{ 0x67b27ec1, "tty_std_termios" },
	{ 0xcacb0550, "alloc_tty_driver" },
	{ 0xf065e692, "tty_wakeup" },
	{ 0xb8e25037, "tty_flip_buffer_push" },
	{ 0x8384a2c5, "tty_unlock" },
	{ 0x24d828d3, "tty_insert_flip_string_fixed_flag" },
	{ 0x61651be, "strcat" },
	{ 0xed302f0f, "tty_lock" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A838779907BC59F5D912B66");

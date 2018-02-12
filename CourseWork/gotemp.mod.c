#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x1deb9105, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x62aea950, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x475bfdbb, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x1b71d3ec, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x745482cd, __VMLINUX_SYMBOL_STR(usb_interrupt_msg) },
	{ 0xf1943569, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xef551010, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2cf1909a, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v1532p0042d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "DBAD4002E8E3153251C341C");

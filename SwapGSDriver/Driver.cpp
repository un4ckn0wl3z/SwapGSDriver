#include <ntifs.h>
#include <ntddk.h>


EXTERN_C void my_swapgs(UINT64* gs_base, UINT64* kernel_gs_base);

// Unload driver handler
void DriverUnload(PDRIVER_OBJECT DriverObject)
{
	DbgPrintEx(0, 0,"SwapGSDriver::DriverUnload:: Driver Unloaded\n");
	UNREFERENCED_PARAMETER(DriverObject);
}

// Driver EntryPoint
// DriverObject: Driver object itself
// RegistryPath: Driver service path
EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	// Code is always run in kernel mode
	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = DriverUnload;

	UINT64 old_kernel_gs_base = 0, old_gs_base = 0, new_kernel_gs_base = 0, new_gs_base = 0;
	my_swapgs(&old_gs_base, &old_kernel_gs_base);
	DbgPrintEx(0, 0, "SwapGSDriver::DriverEntry-> old_gs_base: %p, old_kernel_gs_base: %p\n", old_gs_base, old_kernel_gs_base);

	my_swapgs(&new_gs_base, &new_kernel_gs_base);
	DbgPrintEx(0, 0, "SwapGSDriver::DriverEntry-> new_gs_base: %p, new_kernel_gs_base: %p\n", new_gs_base, new_kernel_gs_base);

	return STATUS_SUCCESS;
}
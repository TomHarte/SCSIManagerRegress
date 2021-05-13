#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace {

//	The standard SCSI driver applied to disks by Apple HD SC Setup prior to the introduction
//	of SCSI Manager 4.3. This driver is known to be compatible at least as far back as the
//	Macintosh Plus, the first model with SCSI.
constexpr uint8_t driver[] = {
	0x60, 0x00, 0x01, 0xba, 0x23, 0x24, 0x00, 0x01, 0x00, 0x27, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x13, 0x9e, 0x00, 0x00, 0xda, 0xe7, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56,
	0x00, 0x7c, 0x00, 0x68, 0x00, 0x72, 0x00, 0x5e, 0x07, 0x2e, 0x53, 0x43, 0x53, 0x49, 0x30, 0x30, 0x41, 0xbd, 0x30, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x1f, 0x60, 0x00,
	0x02, 0x12, 0x41, 0xfa, 0xff, 0xf4, 0x20, 0xaf, 0x00, 0x04, 0x4e, 0x75, 0x20, 0x3a, 0xff, 0xea, 0x4e, 0x75, 0x20, 0x0d, 0x2a, 0x7a, 0xff, 0xe2, 0x4e, 0x75, 0x41, 0xfa, 0xff, 0xd8, 0x30, 0xaf,
	0x00, 0x06, 0x4e, 0x75, 0x48, 0x7a, 0x00, 0x4e, 0x20, 0x1f, 0x4e, 0x75, 0x70, 0x00, 0x31, 0x40, 0x00, 0x10, 0x60, 0x2a, 0x2f, 0x08, 0x2f, 0x09, 0x4e, 0xba, 0x05, 0x4a, 0x60, 0x1c, 0x2f, 0x08,
	0x2f, 0x09, 0x4e, 0xba, 0x07, 0x82, 0x60, 0x12, 0x2f, 0x08, 0x2f, 0x09, 0x4e, 0xba, 0x08, 0xca, 0x60, 0x08, 0x2f, 0x08, 0x2f, 0x09, 0x4e, 0xba, 0x05, 0xf2, 0x22, 0x5f, 0x20, 0x5f, 0x4a, 0x40,
	0x67, 0x04, 0x31, 0xc0, 0x01, 0x42, 0x08, 0x28, 0x00, 0x09, 0x00, 0x06, 0x66, 0x04, 0x2f, 0x38, 0x08, 0xfc, 0x4e, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe,
	0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x88, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01,
	0x80, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x53, 0x43, 0x53, 0x49, 0x20, 0x30, 0x00, 0x48, 0xe7, 0x3f, 0x3e,
	0x49, 0xfa, 0xfe, 0x50, 0x26, 0x14, 0x42, 0x94, 0x70, 0x00, 0x42, 0x42, 0x28, 0x3a, 0xfe, 0x40, 0x53, 0x44, 0x49, 0xfa, 0xfe, 0x2c, 0x14, 0x1c, 0xd0, 0x42, 0xe3, 0x58, 0x51, 0xcc, 0xff, 0xf8,
	0x4a, 0x40, 0x66, 0x02, 0x53, 0x40, 0x49, 0xfa, 0xfe, 0x2a, 0x28, 0x80, 0xb6, 0x80, 0x67, 0x0e, 0x49, 0xfa, 0xfe, 0x20, 0x38, 0x83, 0x4c, 0xdf, 0x7c, 0xfc, 0x70, 0xff, 0x4e, 0x75, 0x28, 0x48,
	0x41, 0xfa, 0xfd, 0xfe, 0x20, 0x3a, 0xfe, 0x08, 0xa0, 0x20, 0x70, 0x06, 0x22, 0x78, 0x01, 0x1c, 0xd2, 0xfc, 0x00, 0x9c, 0x24, 0x21, 0x67, 0x1e, 0x24, 0x42, 0x20, 0x52, 0x24, 0x50, 0x0c, 0xaa,
	0x41, 0xbd, 0x30, 0xb0, 0x00, 0x1a, 0x66, 0x0e, 0xb6, 0xaa, 0xff, 0xfc, 0x66, 0x08, 0x41, 0xfa, 0xfd, 0xd0, 0x4e, 0xea, 0x00, 0x26, 0x51, 0xc8, 0xff, 0xdc, 0x4a, 0x85, 0x6b, 0x14, 0x20, 0x78,
	0x02, 0xa6, 0x20, 0x50, 0xd0, 0xfc, 0x1f, 0x40, 0x2f, 0x38, 0x01, 0x18, 0xa0, 0x57, 0x21, 0xdf, 0x01, 0x18, 0x70, 0x20, 0xd0, 0x45, 0x38, 0x00, 0x46, 0x40, 0xa0, 0x3d, 0xe5, 0x44, 0x22, 0x78,
	0x01, 0x1c, 0x20, 0x71, 0x40, 0x00, 0x2c, 0x50, 0xa0, 0x29, 0x41, 0xfa, 0xfd, 0xaa, 0x2c, 0x88, 0x3d, 0x58, 0x00, 0x04, 0x2d, 0x58, 0x00, 0x22, 0x3d, 0x58, 0x00, 0x26, 0x08, 0xee, 0x00, 0x05,
	0x00, 0x05, 0x08, 0xae, 0x00, 0x06, 0x00, 0x05, 0x70, 0x01, 0x08, 0x05, 0x00, 0x1e, 0x67, 0x02, 0x70, 0x00, 0x2f, 0x00, 0x2f, 0x0e, 0x4e, 0xba, 0x00, 0x3c, 0x50, 0x8f, 0x4a, 0x40, 0x67, 0x02,
	0x70, 0xe9, 0x4c, 0xdf, 0x7c, 0xfc, 0x4e, 0x75, 0x2f, 0x02, 0x42, 0x67, 0x2f, 0x2f, 0x00, 0x0a, 0x3f, 0x3c, 0x00, 0x01, 0x3f, 0x3c, 0x00, 0x03, 0xa8, 0x95, 0x54, 0x8f, 0x24, 0x1f, 0x4e, 0x75,
	0x2f, 0x02, 0x42, 0x67, 0x2f, 0x2f, 0x00, 0x0a, 0x3f, 0x3c, 0x00, 0x04, 0xa8, 0x95, 0x54, 0x8f, 0x24, 0x1f, 0x4e, 0x75, 0x4e, 0x56, 0xfd, 0xf4, 0x48, 0xe7, 0x3e, 0x30, 0x26, 0x6e, 0x00, 0x08,
	0x24, 0x2e, 0x00, 0x0c, 0x4e, 0xba, 0xfd, 0x66, 0x4a, 0x80, 0x67, 0x0c, 0x4e, 0xba, 0xfd, 0x64, 0x2d, 0x40, 0xff, 0xf6, 0x60, 0x00, 0x00, 0x9a, 0x4e, 0xba, 0x0e, 0xde, 0x28, 0x00, 0x4e, 0xba,
	0x0e, 0xe8, 0x2f, 0x00, 0x4e, 0xba, 0x0e, 0xd8, 0x4e, 0xba, 0x0f, 0x92, 0x26, 0x00, 0x2f, 0x04, 0x4e, 0xba, 0x0e, 0xcc, 0x4a, 0x83, 0x50, 0x8f, 0x66, 0x06, 0x70, 0xff, 0x60, 0x00, 0x02, 0x9c,
	0x2f, 0x03, 0x4e, 0xba, 0x0f, 0x48, 0x2f, 0x03, 0x4e, 0xba, 0xfd, 0x18, 0x4e, 0xba, 0xfd, 0x24, 0x2d, 0x40, 0xff, 0xf6, 0x20, 0x38, 0x02, 0xae, 0x50, 0x80, 0x24, 0x40, 0x1b, 0x52, 0xfc, 0x70,
	0x50, 0x8f, 0x66, 0x06, 0x42, 0x2d, 0xfc, 0x74, 0x60, 0x14, 0x1b, 0x7c, 0x00, 0x01, 0xfc, 0x74, 0x0c, 0x2d, 0x00, 0x03, 0xfc, 0x70, 0x65, 0x06, 0x1b, 0x7c, 0x00, 0x02, 0xfc, 0x70, 0x42, 0x6d,
	0xfc, 0x88, 0x42, 0xa7, 0x4e, 0xba, 0xfc, 0xf4, 0x42, 0x6d, 0xfc, 0x8c, 0x42, 0x2d, 0xfc, 0x78, 0x78, 0x00, 0x58, 0x8f, 0x60, 0x0e, 0x20, 0x04, 0xd0, 0x80, 0x41, 0xed, 0xfc, 0x90, 0x42, 0x70,
	0x08, 0x00, 0x52, 0x84, 0x70, 0x08, 0xb0, 0x84, 0x62, 0x00, 0xff, 0xec, 0x42, 0x2d, 0xfc, 0x7c, 0x36, 0x2b, 0x00, 0x18, 0x46, 0x43, 0x04, 0x43, 0x00, 0x20, 0x72, 0x00, 0x32, 0x03, 0x20, 0x01,
	0xc2, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x45, 0xed, 0xfc, 0xa0, 0xd5, 0xc1, 0x4e, 0xba, 0xfc, 0x94, 0x27, 0x40, 0x00, 0x14, 0x42, 0xa7,
	0x70, 0x00, 0x30, 0x03, 0x2f, 0x00, 0x4e, 0xba, 0x07, 0x62, 0x42, 0x46, 0x42, 0x6e, 0xff, 0xfe, 0x7a, 0x01, 0x2d, 0x45, 0xff, 0xfa, 0x78, 0x01, 0x50, 0x8f, 0x60, 0x00, 0x01, 0x50, 0x48, 0x6e,
	0xfd, 0xf6, 0x2f, 0x04, 0x48, 0x78, 0x00, 0x01, 0x42, 0xa7, 0x70, 0x00, 0x30, 0x03, 0x2f, 0x00, 0x4e, 0xba, 0x08, 0x58, 0x3a, 0x00, 0x4f, 0xef, 0x00, 0x14, 0x67, 0x08, 0x0c, 0x45, 0xff, 0xfc,
	0x66, 0x00, 0x01, 0x28, 0x0c, 0x6e, 0x50, 0x4d, 0xfd, 0xf6, 0x66, 0x00, 0x01, 0x1e, 0x70, 0x01, 0xb0, 0x84, 0x66, 0x06, 0x2d, 0x6e, 0xfd, 0xfa, 0xff, 0xfa, 0x4a, 0x6e, 0xff, 0xfe, 0x66, 0x4e,
	0x41, 0xee, 0xfe, 0x26, 0x0c, 0x90, 0x41, 0x70, 0x70, 0x6c, 0x66, 0x42, 0x41, 0xee, 0xfe, 0x2a, 0x0c, 0x90, 0x65, 0x5f, 0x44, 0x72, 0x66, 0x36, 0x0c, 0xae, 0x00, 0x01, 0x06, 0x00, 0xfe, 0x7e,
	0x66, 0x2c, 0x72, 0x01, 0x3d, 0x41, 0xff, 0xfe, 0x70, 0x00, 0x30, 0x03, 0xd0, 0x80, 0x41, 0xed, 0xfc, 0x90, 0x31, 0xae, 0xfe, 0x8c, 0x08, 0x00, 0x35, 0x6e, 0xfe, 0x84, 0x00, 0x2c, 0x15, 0x6e,
	0xfe, 0x89, 0x00, 0x25, 0x15, 0x6e, 0xfe, 0x8b, 0x00, 0x27, 0x60, 0x00, 0x00, 0xbe, 0x4a, 0x46, 0x66, 0x00, 0x00, 0xb8, 0x41, 0xee, 0xfe, 0x26, 0x0c, 0x90, 0x41, 0x70, 0x70, 0x6c, 0x66, 0x00,
	0x00, 0xaa, 0x41, 0xee, 0xfe, 0x2a, 0x0c, 0x90, 0x65, 0x5f, 0x48, 0x46, 0x66, 0x00, 0x00, 0x9c, 0x7c, 0x01, 0x7a, 0x08, 0x20, 0x78, 0x03, 0x0a, 0x60, 0x0e, 0x30, 0x28, 0x00, 0x06, 0xb0, 0x45,
	0x66, 0x04, 0x52, 0x45, 0x60, 0xee, 0x20, 0x50, 0x20, 0x08, 0x66, 0x00, 0xff, 0xee, 0x42, 0x52, 0x08, 0x2e, 0x00, 0x05, 0xfe, 0x51, 0x67, 0x04, 0x70, 0x00, 0x60, 0x06, 0x20, 0x3c, 0x00, 0x00,
	0x00, 0x80, 0x15, 0x40, 0x00, 0x02, 0x15, 0x7c, 0x00, 0x08, 0x00, 0x03, 0x15, 0x7c, 0x00, 0x01, 0x00, 0x04, 0x42, 0x2a, 0x00, 0x05, 0x35, 0x7c, 0x00, 0x01, 0x00, 0x0a, 0x42, 0xaa, 0x00, 0x06,
	0x42, 0x6a, 0x00, 0x10, 0x35, 0x6e, 0xfe, 0x4c, 0x00, 0x12, 0x20, 0x2e, 0xfe, 0x4a, 0x72, 0x10, 0xe2, 0xa8, 0x35, 0x40, 0x00, 0x14, 0x20, 0x2e, 0xfe, 0x46, 0xd0, 0xae, 0xfd, 0xfe, 0x25, 0x40,
	0x00, 0x18, 0x25, 0x40, 0x00, 0x1c, 0x25, 0x6e, 0xfe, 0x4a, 0x00, 0x20, 0x35, 0x45, 0x00, 0x16, 0x48, 0x6a, 0x00, 0x06, 0x70, 0x00, 0x30, 0x05, 0x2f, 0x00, 0x30, 0x2b, 0x00, 0x18, 0x48, 0xc0,
	0x2f, 0x00, 0x4e, 0xba, 0x0c, 0x98, 0x4f, 0xef, 0x00, 0x0c, 0x52, 0x84, 0xb8, 0xae, 0xff, 0xfa, 0x63, 0x00, 0xfe, 0xac, 0x4a, 0x6e, 0xff, 0xfe, 0x66, 0x06, 0x7a, 0xfe, 0x60, 0x00, 0x00, 0x6e,
	0x4a, 0x46, 0x66, 0x04, 0x42, 0x45, 0x60, 0x64, 0x70, 0x00, 0x30, 0x03, 0x41, 0xed, 0xfc, 0x80, 0x11, 0xbc, 0x00, 0x01, 0x08, 0x00, 0x70, 0x01, 0x12, 0x03, 0xe3, 0xa0, 0x36, 0x00, 0x4a, 0x82,
	0x67, 0x06, 0x30, 0x03, 0x81, 0x6d, 0xfc, 0x8c, 0x4a, 0x6d, 0xfc, 0x88, 0x66, 0x28, 0x3b, 0x7c, 0x00, 0x01, 0xfc, 0x64, 0x41, 0xfa, 0x04, 0x58, 0x2b, 0x48, 0xfc, 0x66, 0x3b, 0x7c, 0x00, 0x65,
	0xfc, 0x6a, 0x42, 0x6d, 0xfc, 0x6c, 0x48, 0x6d, 0xfc, 0x60, 0x4e, 0xba, 0x0c, 0xc0, 0x1b, 0x7c, 0x00, 0x01, 0xfc, 0x7c, 0x58, 0x8f, 0x30, 0x03, 0x81, 0x6d, 0xfc, 0x88, 0x70, 0x00, 0x30, 0x2d,
	0xfc, 0x88, 0x2f, 0x00, 0x4e, 0xba, 0xfa, 0xb4, 0x42, 0x45, 0x58, 0x8f, 0x2f, 0x2e, 0xff, 0xf6, 0x4e, 0xba, 0x0c, 0xe4, 0x30, 0x05, 0x48, 0xc0, 0x58, 0x8f, 0x4c, 0xee, 0x0c, 0x7c, 0xfd, 0xd8,
	0x4e, 0x5e, 0x4e, 0x75, 0x48, 0xe7, 0x38, 0x20, 0x24, 0x6f, 0x00, 0x14, 0x20, 0x2f, 0x00, 0x18, 0x4e, 0xba, 0xfa, 0x80, 0x28, 0x00, 0x34, 0x2a, 0x00, 0x18, 0x46, 0x42, 0x04, 0x42, 0x00, 0x20,
	0x70, 0x01, 0x12, 0x02, 0xe3, 0xa0, 0x46, 0x40, 0xc1, 0x6d, 0xfc, 0x88, 0x70, 0x00, 0x30, 0x2d, 0xfc, 0x88, 0x2f, 0x00, 0x4e, 0xba, 0xfa, 0x64, 0x36, 0x2d, 0xfc, 0x88, 0x48, 0x78, 0x03, 0x08,
	0x32, 0x02, 0x48, 0xc1, 0x20, 0x01, 0xc2, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x41, 0xed, 0xfc, 0xa0, 0x48, 0x70, 0x18, 0x06, 0x4e, 0xba,
	0x0c, 0x04, 0x4a, 0x43, 0x4f, 0xef, 0x00, 0x0c, 0x66, 0x22, 0x4a, 0x2d, 0xfc, 0x7c, 0x67, 0x0a, 0x48, 0x6d, 0xfc, 0x60, 0x4e, 0xba, 0x0c, 0x20, 0x58, 0x8f, 0x4a, 0x2d, 0xfc, 0x78, 0x67, 0x0c,
	0x45, 0xfa, 0x04, 0x40, 0x2f, 0x0a, 0x4e, 0xba, 0xfc, 0x78, 0x58, 0x8f, 0x2f, 0x04, 0x4e, 0xba, 0x0c, 0x46, 0x4a, 0x43, 0x58, 0x8f, 0x66, 0x2a, 0x4e, 0xba, 0x0b, 0x7e, 0x24, 0x00, 0x4e, 0xba,
	0x0b, 0x88, 0x2f, 0x00, 0x4e, 0xba, 0x0b, 0x78, 0x4e, 0xba, 0xf9, 0xe2, 0x2f, 0x00, 0x4e, 0xba, 0x0c, 0x3c, 0x2f, 0x02, 0x4e, 0xba, 0x0b, 0x68, 0x42, 0xa7, 0x4e, 0xba, 0xf9, 0xc6, 0x4f, 0xef,
	0x00, 0x10, 0x70, 0x00, 0x4c, 0xdf, 0x04, 0x1c, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xf0, 0x48, 0xe7, 0x3e, 0x38, 0x24, 0x2e, 0x00, 0x08, 0x24, 0x6e, 0x00, 0x0c, 0x4e, 0xba, 0xf9, 0xb6, 0x2d, 0x40,
	0xff, 0xf2, 0x28, 0x42, 0x3c, 0x2c, 0x00, 0x18, 0x46, 0x46, 0x04, 0x46, 0x00, 0x20, 0x32, 0x06, 0x48, 0xc1, 0x20, 0x01, 0xc2, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40,
	0x42, 0x40, 0xd2, 0x80, 0x47, 0xed, 0xfc, 0xa0, 0xd7, 0xc1, 0x78, 0x00, 0x0c, 0x2a, 0x00, 0x03, 0x00, 0x07, 0x57, 0xc4, 0x44, 0x04, 0x28, 0x42, 0x2d, 0x6c, 0x00, 0x10, 0xff, 0xfc, 0x70, 0x09,
	0x26, 0x2e, 0xff, 0xfc, 0xe0, 0xa3, 0x2d, 0x43, 0xff, 0xfc, 0x2d, 0x6a, 0x00, 0x24, 0xff, 0xf8, 0x70, 0x09, 0x26, 0x2e, 0xff, 0xf8, 0xe0, 0xa3, 0x2d, 0x43, 0xff, 0xf8, 0x30, 0x2b, 0x00, 0x16,
	0xb0, 0x6a, 0x00, 0x16, 0x67, 0x06, 0x76, 0xc8, 0x60, 0x00, 0x00, 0xe4, 0x20, 0x2a, 0x00, 0x24, 0x02, 0x80, 0x00, 0x00, 0x01, 0xff, 0x66, 0x00, 0x00, 0x18, 0x4a, 0xab, 0x00, 0x1c, 0x67, 0x16,
	0x20, 0x2b, 0x00, 0x20, 0x22, 0x2e, 0xff, 0xf8, 0xd2, 0xae, 0xff, 0xfc, 0xb0, 0x81, 0x64, 0x06, 0x76, 0xce, 0x60, 0x00, 0x00, 0xba, 0x30, 0x06, 0x48, 0xc0, 0x41, 0xed, 0xfc, 0x80, 0x4a, 0x30,
	0x08, 0x00, 0x67, 0x20, 0x30, 0x06, 0x48, 0xc0, 0x41, 0xed, 0xfc, 0x80, 0x42, 0x30, 0x08, 0x00, 0x70, 0x00, 0x10, 0x2d, 0xfc, 0x74, 0x2f, 0x00, 0x30, 0x06, 0x48, 0xc0, 0x2f, 0x00, 0x4e, 0xba,
	0x03, 0xca, 0x50, 0x8f, 0x08, 0x2a, 0x00, 0x06, 0x00, 0x2d, 0x67, 0x0a, 0x4a, 0x44, 0x66, 0x06, 0x42, 0x43, 0x60, 0x00, 0x00, 0x6c, 0x42, 0x6e, 0xff, 0xf6, 0x7a, 0xff, 0x2f, 0x2a, 0x00, 0x20,
	0x20, 0x2b, 0x00, 0x1c, 0xd0, 0xae, 0xff, 0xfc, 0x2f, 0x00, 0x2f, 0x2e, 0xff, 0xf8, 0x30, 0x04, 0x48, 0xc0, 0x2f, 0x00, 0x30, 0x06, 0x48, 0xc0, 0x2f, 0x00, 0x4e, 0xba, 0x04, 0xae, 0x36, 0x00,
	0x4f, 0xef, 0x00, 0x14, 0x67, 0x3a, 0x53, 0x43, 0x66, 0x10, 0x2f, 0x2b, 0x00, 0x28, 0x30, 0x06, 0x48, 0xc0, 0x2f, 0x00, 0x4e, 0xba, 0x07, 0x42, 0x50, 0x8f, 0xba, 0xab, 0x00, 0x28, 0x66, 0x06,
	0x52, 0x6e, 0xff, 0xf6, 0x60, 0x08, 0x42, 0x6e, 0xff, 0xf6, 0x2a, 0x2b, 0x00, 0x28, 0x0c, 0x6e, 0x00, 0x04, 0xff, 0xf6, 0x6d, 0x00, 0xff, 0xa6, 0x76, 0xdc, 0x42, 0xaa, 0x00, 0x28, 0x60, 0x0e,
	0x20, 0x2a, 0x00, 0x24, 0x25, 0x40, 0x00, 0x28, 0x20, 0x42, 0xd1, 0xa8, 0x00, 0x10, 0x2f, 0x2e, 0xff, 0xf2, 0x4e, 0xba, 0x0a, 0xa2, 0x30, 0x03, 0x48, 0xc0, 0x58, 0x8f, 0x4c, 0xee, 0x1c, 0x7c,
	0xff, 0xd0, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xfd, 0xfc, 0x48, 0xe7, 0x3c, 0x30, 0x26, 0x6e, 0x00, 0x08, 0x24, 0x6e, 0x00, 0x0c, 0x4e, 0xba, 0xf8, 0x3a, 0x2a, 0x00, 0x38, 0x2b, 0x00, 0x18,
	0x46, 0x44, 0x04, 0x44, 0x00, 0x20, 0x30, 0x04, 0x48, 0xc0, 0x24, 0x00, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x42, 0xc4, 0xfc, 0x00, 0x6c, 0x48, 0x42, 0x42, 0x42, 0xd0, 0x82, 0x41, 0xed, 0xfc, 0xa0,
	0xd1, 0xc0, 0x42, 0x43, 0x0c, 0x6a, 0x00, 0x41, 0x00, 0x1a, 0x66, 0x44, 0x4a, 0x2d, 0xfc, 0x78, 0x66, 0x34, 0x48, 0x78, 0x00, 0x01, 0x48, 0x78, 0x00, 0x9f, 0x4e, 0xba, 0x09, 0xda, 0x24, 0x00,
	0x48, 0x78, 0x00, 0x01, 0x48, 0x78, 0x00, 0x95, 0x4e, 0xba, 0x09, 0xcc, 0xb4, 0x80, 0x4f, 0xef, 0x00, 0x10, 0x67, 0x12, 0x45, 0xfa, 0x02, 0x0c, 0x2f, 0x0a, 0x4e, 0xba, 0xfa, 0x2c, 0x1b, 0x7c,
	0x00, 0x01, 0xfc, 0x78, 0x58, 0x8f, 0x02, 0x6b, 0x4f, 0xff, 0x00, 0x04, 0x60, 0x00, 0x00, 0xb2, 0x30, 0x28, 0x00, 0x16, 0xb0, 0x6a, 0x00, 0x16, 0x67, 0x06, 0x76, 0xc8, 0x60, 0x00, 0x00, 0xa2,
	0x30, 0x2a, 0x00, 0x1a, 0x0c, 0x40, 0x00, 0x07, 0x6d, 0x06, 0x6e, 0x1e, 0x60, 0x00, 0x00, 0x7e, 0x0c, 0x40, 0x00, 0x05, 0x6d, 0x00, 0x00, 0x88, 0x6e, 0x04, 0x60, 0x00, 0x00, 0x84, 0x0c, 0x40,
	0x00, 0x06, 0x66, 0x00, 0x00, 0x7a, 0x60, 0x00, 0x00, 0x78, 0x0c, 0x40, 0x00, 0x11, 0x6d, 0x00, 0x00, 0x6e, 0x6e, 0x02, 0x60, 0x08, 0x0c, 0x40, 0x00, 0x15, 0x66, 0x62, 0x60, 0x18, 0x43, 0xea,
	0x00, 0x1c, 0x0c, 0x51, 0x00, 0x01, 0x66, 0x06, 0x42, 0xa8, 0x00, 0x1c, 0x60, 0x52, 0x21, 0x68, 0x00, 0x18, 0x00, 0x1c, 0x60, 0x4a, 0x4e, 0xba, 0xf7, 0x6c, 0x2d, 0x40, 0xff, 0xfc, 0x20, 0x2e,
	0xff, 0xfc, 0x06, 0x80, 0x00, 0x00, 0x01, 0x00, 0x5c, 0x80, 0x32, 0x04, 0x48, 0xc1, 0x74, 0x30, 0xd2, 0x82, 0x26, 0x40, 0x16, 0x81, 0x48, 0x78, 0x00, 0x04, 0x48, 0x6e, 0xff, 0xfc, 0x48, 0x6a,
	0x00, 0x1c, 0x4e, 0xba, 0x08, 0x02, 0x4f, 0xef, 0x00, 0x0c, 0x60, 0x14, 0x70, 0x00, 0x30, 0x28, 0x00, 0x16, 0x2f, 0x00, 0x48, 0x78, 0x00, 0x07, 0x4e, 0xba, 0x08, 0xdc, 0x50, 0x8f, 0x76, 0xef,
	0x2f, 0x05, 0x4e, 0xba, 0x09, 0x52, 0x34, 0x03, 0x48, 0xc2, 0x58, 0x8f, 0x20, 0x02, 0x4c, 0xee, 0x0c, 0x3c, 0xfd, 0xe4, 0x4e, 0x5e, 0x4e, 0x75, 0x48, 0xe7, 0x30, 0x30, 0x26, 0x6f, 0x00, 0x14,
	0x24, 0x6f, 0x00, 0x18, 0x42, 0x42, 0x4e, 0xba, 0xf6, 0xea, 0x26, 0x00, 0x32, 0x2b, 0x00, 0x18, 0x46, 0x41, 0x04, 0x41, 0x00, 0x20, 0x48, 0xc1, 0x20, 0x01, 0xc2, 0xfc, 0x00, 0x6c, 0x48, 0x40,
	0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x41, 0xed, 0xfc, 0xa0, 0xd1, 0xc1, 0x30, 0x28, 0x00, 0x16, 0xb0, 0x6a, 0x00, 0x16, 0x67, 0x04, 0x74, 0xc8, 0x60, 0x1e, 0x30, 0x2a,
	0x00, 0x1a, 0x51, 0x40, 0x66, 0x14, 0x48, 0x78, 0x00, 0x16, 0x48, 0x50, 0x48, 0x6a, 0x00, 0x1c, 0x4e, 0xba, 0x07, 0x74, 0x4f, 0xef, 0x00, 0x0c, 0x60, 0x02, 0x74, 0xee, 0x2f, 0x03, 0x4e, 0xba,
	0x08, 0xd6, 0x30, 0x02, 0x48, 0xc0, 0x58, 0x8f, 0x4c, 0xdf, 0x0c, 0x0c, 0x4e, 0x75, 0x48, 0xe7, 0x38, 0x00, 0x4e, 0xba, 0xf6, 0x7e, 0x28, 0x00, 0x3b, 0x7c, 0x00, 0x65, 0xfc, 0x6a, 0x4a, 0x6d,
	0xfc, 0x8c, 0x67, 0x58, 0x36, 0x3c, 0x00, 0x80, 0x74, 0x07, 0x72, 0x00, 0x32, 0x2d, 0xfc, 0x8c, 0x30, 0x03, 0x48, 0xc0, 0xc2, 0x80, 0x67, 0x38, 0x32, 0x02, 0x48, 0xc1, 0x20, 0x01, 0xc2, 0xfc,
	0x00, 0x6c, 0x48, 0x40, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x41, 0xed, 0xfc, 0xa0, 0x70, 0x00, 0x30, 0x30, 0x18, 0x16, 0x2f, 0x00, 0x48, 0x78, 0x00, 0x07, 0x4e, 0xba,
	0x07, 0xf6, 0x4a, 0x80, 0x50, 0x8f, 0x66, 0x08, 0x30, 0x03, 0x46, 0x40, 0xc1, 0x6d, 0xfc, 0x8c, 0x30, 0x03, 0xe2, 0x40, 0x36, 0x00, 0x53, 0x42, 0x6c, 0x00, 0xff, 0xb0, 0x4a, 0x2d, 0xfc, 0x74,
	0x66, 0x32, 0x22, 0x38, 0x02, 0xae, 0x20, 0x38, 0x0c, 0x54, 0x02, 0x80, 0x00, 0xff, 0xff, 0xff, 0xb2, 0x80, 0x63, 0x20, 0x1b, 0x7c, 0x00, 0x01, 0xfc, 0x74, 0x42, 0x42, 0x30, 0x02, 0x48, 0xc0,
	0x41, 0xed, 0xfc, 0x80, 0x11, 0xbc, 0x00, 0x01, 0x08, 0x00, 0x52, 0x42, 0x0c, 0x42, 0x00, 0x08, 0x6d, 0x00, 0xff, 0xea, 0x2f, 0x04, 0x4e, 0xba, 0x08, 0x1e, 0x58, 0x8f, 0x4c, 0xdf, 0x00, 0x1c,
	0x4e, 0x75, 0x4e, 0x56, 0xff, 0xf8, 0x48, 0xe7, 0x3c, 0x00, 0x4e, 0xba, 0xf5, 0xc6, 0x2a, 0x00, 0x48, 0x78, 0x00, 0x06, 0x48, 0x78, 0x00, 0x1b, 0x48, 0x6e, 0xff, 0xfa, 0x4e, 0xba, 0x06, 0xa2,
	0x70, 0x01, 0x12, 0x2d, 0xfc, 0x70, 0xe3, 0xa0, 0x38, 0x00, 0x74, 0x00, 0x4f, 0xef, 0x00, 0x0c, 0x20, 0x02, 0xd0, 0x80, 0x41, 0xed, 0xfc, 0x90, 0x36, 0x30, 0x08, 0x00, 0x70, 0x00, 0x30, 0x04,
	0x72, 0x00, 0x32, 0x03, 0xc0, 0x81, 0x67, 0x46, 0x4a, 0x82, 0x67, 0x00, 0x00, 0x0e, 0x70, 0x00, 0x30, 0x03, 0x02, 0x80, 0x00, 0x00, 0x40, 0x00, 0x66, 0x34, 0x70, 0x00, 0x30, 0x03, 0x02, 0x80,
	0x00, 0x00, 0x80, 0x00, 0x67, 0x08, 0x1d, 0x7c, 0x00, 0x01, 0xff, 0xfb, 0x60, 0x04, 0x42, 0x2e, 0xff, 0xfb, 0x48, 0x78, 0x03, 0x84, 0x42, 0xa7, 0x42, 0xa7, 0x42, 0xa7, 0x2f, 0x02, 0x48, 0x78,
	0x00, 0x06, 0x48, 0x6e, 0xff, 0xfa, 0x4e, 0xba, 0x02, 0x70, 0x4f, 0xef, 0x00, 0x1c, 0x52, 0x82, 0x70, 0x08, 0xb0, 0x82, 0x6e, 0x00, 0xff, 0x9a, 0x2f, 0x05, 0x4e, 0xba, 0x07, 0x7a, 0x58, 0x8f,
	0x4c, 0xee, 0x00, 0x3c, 0xff, 0xe8, 0x4e, 0x5e, 0x4e, 0x75, 0x48, 0xe7, 0x30, 0x00, 0x22, 0x2f, 0x00, 0x0c, 0x26, 0x2f, 0x00, 0x10, 0x20, 0x01, 0xc2, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0xc0, 0xfc,
	0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x41, 0xed, 0xfc, 0xa0, 0xd1, 0xc1, 0x22, 0x48, 0x70, 0x01, 0xb0, 0x83, 0x66, 0x1a, 0x70, 0x00, 0x10, 0x29, 0x00, 0x27, 0x72, 0x01, 0x14, 0x2d,
	0xfc, 0x70, 0xe5, 0xa1, 0xc0, 0x81, 0x67, 0x08, 0x13, 0x7c, 0x00, 0x01, 0x00, 0x26, 0x60, 0x04, 0x42, 0x29, 0x00, 0x26, 0x33, 0x7c, 0x00, 0x01, 0x00, 0x30, 0x4a, 0x83, 0x67, 0x00, 0x00, 0x08,
	0x4a, 0x29, 0x00, 0x25, 0x66, 0x16, 0x42, 0x29, 0x00, 0x24, 0x23, 0x7c, 0x00, 0x00, 0x02, 0x00, 0x00, 0x36, 0x33, 0x7c, 0x00, 0x07, 0x00, 0x3a, 0x60, 0x00, 0x00, 0xaa, 0x13, 0x69, 0x00, 0x25,
	0x00, 0x24, 0x70, 0x00, 0x10, 0x29, 0x00, 0x24, 0x0c, 0x40, 0x00, 0x01, 0x6d, 0x00, 0x00, 0x96, 0x6e, 0x02, 0x60, 0x08, 0x55, 0x40, 0x66, 0x00, 0x00, 0x8c, 0x60, 0x22, 0x23, 0x7c, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x36, 0x33, 0x7c, 0x00, 0x05, 0x00, 0x3a, 0x70, 0xf6, 0x23, 0x40, 0x00, 0x3c, 0x33, 0x7c, 0x00, 0x07, 0x00, 0x44, 0x33, 0x7c, 0x00, 0x01, 0x00, 0x2e, 0x60, 0x66, 0x70, 0x00,
	0x30, 0x29, 0x00, 0x2c, 0x23, 0x40, 0x00, 0x36, 0x33, 0x7c, 0x00, 0x04, 0x00, 0x3a, 0x41, 0xe9, 0x00, 0x32, 0x23, 0x48, 0x00, 0x3c, 0x41, 0xe9, 0x00, 0x46, 0x23, 0x48, 0x00, 0x40, 0x33, 0x7c,
	0x00, 0x01, 0x00, 0x44, 0x20, 0x3c, 0x00, 0x00, 0x02, 0x00, 0x72, 0x00, 0x32, 0x29, 0x00, 0x2c, 0x90, 0x81, 0x23, 0x40, 0x00, 0x4a, 0x33, 0x7c, 0x00, 0x04, 0x00, 0x4e, 0x41, 0xe9, 0x00, 0x46,
	0x23, 0x48, 0x00, 0x50, 0x41, 0xe9, 0x00, 0x32, 0x23, 0x48, 0x00, 0x54, 0x33, 0x7c, 0x00, 0x05, 0x00, 0x58, 0x70, 0xd8, 0x23, 0x40, 0x00, 0x5a, 0x33, 0x7c, 0x00, 0x07, 0x00, 0x62, 0x33, 0x7c,
	0x00, 0x04, 0x00, 0x2e, 0x4c, 0xdf, 0x00, 0x0c, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xf0, 0x48, 0xe7, 0x3c, 0x20, 0x38, 0x2e, 0x00, 0x0a, 0x36, 0x2e, 0x00, 0x0e, 0x24, 0x2e, 0x00, 0x10, 0x4a, 0x43,
	0x67, 0x04, 0x70, 0x0a, 0x60, 0x02, 0x70, 0x08, 0x48, 0x78, 0x00, 0x06, 0x2f, 0x00, 0x48, 0x6e, 0xff, 0xf2, 0x4e, 0xba, 0x04, 0xcc, 0x72, 0x00, 0x32, 0x04, 0x20, 0x01, 0xc2, 0xfc, 0x00, 0x6c,
	0x48, 0x40, 0xc0, 0xfc, 0x00, 0x6c, 0x48, 0x40, 0x42, 0x40, 0xd2, 0x80, 0x45, 0xed, 0xfc, 0xa0, 0xd5, 0xc1, 0x25, 0x6e, 0x00, 0x18, 0x00, 0x32, 0x4f, 0xef, 0x00, 0x0c, 0x60, 0x00, 0x00, 0xc8,
	0x20, 0x2e, 0x00, 0x14, 0x72, 0x10, 0xe2, 0xa8, 0x1d, 0x40, 0xff, 0xf3, 0x41, 0xee, 0xff, 0xf4, 0x30, 0xae, 0x00, 0x16, 0x4a, 0x2a, 0x00, 0x24, 0x66, 0x04, 0x7a, 0x01, 0x60, 0x28, 0x0c, 0x82,
	0x00, 0x00, 0x01, 0x00, 0x63, 0x08, 0x2a, 0x3c, 0x00, 0x00, 0x01, 0x00, 0x60, 0x02, 0x2a, 0x02, 0x72, 0x00, 0x32, 0x2a, 0x00, 0x2e, 0xd2, 0x81, 0x20, 0x01, 0xe5, 0x81, 0xd2, 0x80, 0x20, 0x05,
	0x2a, 0x00, 0x25, 0x80, 0x18, 0x36, 0x1d, 0x45, 0xff, 0xf6, 0x48, 0x78, 0x2a, 0x30, 0x70, 0x00, 0x10, 0x2a, 0x00, 0x26, 0x2f, 0x00, 0x70, 0x00, 0x30, 0x03, 0x2f, 0x00, 0x48, 0x6a, 0x00, 0x30,
	0x70, 0x00, 0x30, 0x04, 0x2f, 0x00, 0x48, 0x78, 0x00, 0x06, 0x48, 0x6e, 0xff, 0xf2, 0x4e, 0xba, 0x00, 0x68, 0x30, 0x00, 0x4f, 0xef, 0x00, 0x1c, 0x67, 0x44, 0x0c, 0x40, 0x00, 0x02, 0x67, 0x04,
	0x48, 0xc0, 0x60, 0x4a, 0x48, 0x78, 0x00, 0x08, 0x48, 0x6e, 0xff, 0xf8, 0x70, 0x00, 0x30, 0x04, 0x2f, 0x00, 0x4e, 0xba, 0x01, 0x58, 0x4a, 0x80, 0x4f, 0xef, 0x00, 0x0c, 0x67, 0x04, 0x70, 0xf9,
	0x60, 0x2c, 0x48, 0x78, 0x00, 0x04, 0x48, 0x6e, 0xff, 0xfb, 0x48, 0x6a, 0x00, 0x28, 0x4e, 0xba, 0x03, 0xd6, 0x70, 0x00, 0x10, 0x2e, 0xff, 0xfa, 0x4f, 0xef, 0x00, 0x0c, 0x60, 0x10, 0x94, 0x85,
	0x20, 0x05, 0xd1, 0xae, 0x00, 0x14, 0x4a, 0x82, 0x62, 0x00, 0xff, 0x36, 0x70, 0x00, 0x4c, 0xee, 0x04, 0x3c, 0xff, 0xdc, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xf8, 0x48, 0xe7, 0x3e, 0x00,
	0x26, 0x2e, 0x00, 0x08, 0x38, 0x2e, 0x00, 0x0e, 0x3a, 0x2e, 0x00, 0x12, 0x42, 0x46, 0x42, 0x6e, 0xff, 0xfe, 0x55, 0x8f, 0x4e, 0xba, 0x03, 0xcc, 0x30, 0x1f, 0x48, 0xc0, 0x30, 0x00, 0x67, 0x1e,
	0x52, 0x6e, 0xff, 0xfe, 0x0c, 0x6e, 0x00, 0x03, 0xff, 0xfe, 0x6f, 0x00, 0xff, 0xe6, 0x55, 0x8f, 0x4e, 0xba, 0x04, 0x00, 0x30, 0x1f, 0x08, 0x00, 0x00, 0x06, 0x67, 0xd2, 0x60, 0xf0, 0x55, 0x8f,
	0x3f, 0x05, 0x4e, 0xba, 0x03, 0xa8, 0x30, 0x1f, 0x48, 0xc0, 0x30, 0x00, 0x67, 0x06, 0x70, 0xfe, 0x60, 0x00, 0x00, 0xb0, 0x42, 0x6e, 0xff, 0xfe, 0x55, 0x8f, 0x2f, 0x03, 0x3f, 0x04, 0x4e, 0xba,
	0x03, 0x96, 0x30, 0x1f, 0x48, 0xc0, 0x30, 0x00, 0x67, 0x12, 0x52, 0x6e, 0xff, 0xfe, 0x0c, 0x6e, 0x00, 0x03, 0xff, 0xfe, 0x6f, 0x00, 0xff, 0xe2, 0x7c, 0xfd, 0x60, 0x52, 0x4a, 0xae, 0x00, 0x14,
	0x67, 0x4c, 0x4a, 0x6e, 0x00, 0x1e, 0x67, 0x24, 0x4a, 0x6e, 0x00, 0x1a, 0x67, 0x0c, 0x55, 0x8f, 0x2f, 0x2e, 0x00, 0x14, 0x4e, 0xba, 0x03, 0x92, 0x60, 0x0a, 0x55, 0x8f, 0x2f, 0x2e, 0x00, 0x14,
	0x4e, 0xba, 0x03, 0x7c, 0x30, 0x1f, 0x48, 0xc0, 0x2c, 0x00, 0x60, 0x22, 0x4a, 0x6e, 0x00, 0x1a, 0x67, 0x0c, 0x55, 0x8f, 0x2f, 0x2e, 0x00, 0x14, 0x4e, 0xba, 0x03, 0x5a, 0x60, 0x0a, 0x55, 0x8f,
	0x2f, 0x2e, 0x00, 0x14, 0x4e, 0xba, 0x03, 0x44, 0x30, 0x1f, 0x48, 0xc0, 0x2c, 0x00, 0x55, 0x8f, 0x48, 0x6e, 0xff, 0xfa, 0x48, 0x6e, 0xff, 0xfc, 0x2f, 0x2e, 0x00, 0x20, 0x4e, 0xba, 0x03, 0x22,
	0x30, 0x1f, 0x48, 0xc0, 0x30, 0x00, 0x67, 0x04, 0x70, 0xfc, 0x60, 0x16, 0x4a, 0x46, 0x67, 0x0c, 0x0c, 0x6e, 0x00, 0x02, 0xff, 0xfa, 0x67, 0x04, 0x30, 0x06, 0x60, 0x04, 0x30, 0x2e, 0xff, 0xfa,
	0x48, 0xc0, 0x4c, 0xee, 0x00, 0x7c, 0xff, 0xe4, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xe4, 0x48, 0xe7, 0x38, 0x00, 0x36, 0x2e, 0x00, 0x0a, 0x28, 0x2e, 0x00, 0x0c, 0x34, 0x2e, 0x00, 0x12,
	0x48, 0x78, 0x00, 0x06, 0x48, 0x78, 0x00, 0x03, 0x48, 0x6e, 0xff, 0xe6, 0x4e, 0xba, 0x02, 0x92, 0x1d, 0x42, 0xff, 0xea, 0x3d, 0x7c, 0x00, 0x02, 0xff, 0xec, 0x2d, 0x44, 0xff, 0xee, 0x70, 0x00,
	0x30, 0x02, 0x2d, 0x40, 0xff, 0xf2, 0x3d, 0x7c, 0x00, 0x07, 0xff, 0xf6, 0x48, 0x78, 0x02, 0x58, 0x42, 0xa7, 0x42, 0xa7, 0x48, 0x6e, 0xff, 0xec, 0x30, 0x03, 0x48, 0xc0, 0x2f, 0x00, 0x48, 0x78,
	0x00, 0x06, 0x48, 0x6e, 0xff, 0xe6, 0x4e, 0xba, 0xfe, 0x90, 0x4f, 0xef, 0x00, 0x28, 0x4c, 0xee, 0x00, 0x1c, 0xff, 0xd8, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xf4, 0x48, 0xe7, 0x3e, 0x30,
	0x24, 0x2e, 0x00, 0x08, 0x26, 0x2e, 0x00, 0x0c, 0x4e, 0xba, 0x02, 0xce, 0x2d, 0x40, 0xff, 0xf6, 0x4e, 0xba, 0x02, 0xd6, 0x2f, 0x00, 0x4e, 0xba, 0x02, 0xc6, 0x48, 0x78, 0x04, 0x00, 0x4e, 0xba,
	0x02, 0xd8, 0x24, 0x40, 0xb4, 0xfc, 0x00, 0x00, 0x50, 0x8f, 0x66, 0x1e, 0x4e, 0xba, 0x02, 0xc2, 0x2f, 0x00, 0x4e, 0xba, 0x02, 0xaa, 0x48, 0x78, 0x04, 0x00, 0x4e, 0xba, 0x02, 0xbc, 0x24, 0x40,
	0xb4, 0xfc, 0x00, 0x00, 0x50, 0x8f, 0x67, 0x00, 0x01, 0x16, 0x2f, 0x0a, 0x4e, 0xba, 0x02, 0xbe, 0x26, 0x52, 0x20, 0x4b, 0x41, 0xe8, 0x02, 0x00, 0x2d, 0x48, 0xff, 0xfc, 0x42, 0x6e, 0xff, 0xfa,
	0x58, 0x8f, 0x42, 0x45, 0x42, 0x46, 0x42, 0x44, 0x2f, 0x2e, 0xff, 0xfc, 0x2f, 0x03, 0x48, 0x78, 0x00, 0x01, 0x42, 0xa7, 0x2f, 0x02, 0x4e, 0xba, 0xfc, 0xd2, 0x30, 0x00, 0x4f, 0xef, 0x00, 0x14,
	0x67, 0x20, 0x53, 0x40, 0x66, 0x18, 0x52, 0x46, 0xba, 0x44, 0x66, 0x12, 0x48, 0x78, 0x02, 0x00, 0x2f, 0x2e, 0xff, 0xfc, 0x2f, 0x0b, 0x4e, 0xba, 0x01, 0x8e, 0x4f, 0xef, 0x00, 0x0c, 0x52, 0x45,
	0x60, 0x12, 0x48, 0x78, 0x02, 0x00, 0x2f, 0x2e, 0xff, 0xfc, 0x2f, 0x0b, 0x4e, 0xba, 0x01, 0x78, 0x4f, 0xef, 0x00, 0x0c, 0x52, 0x44, 0x0c, 0x44, 0x00, 0x0a, 0x6d, 0x00, 0xff, 0xac, 0x4a, 0x45,
	0x67, 0x00, 0x00, 0x9c, 0x4a, 0x46, 0x67, 0x00, 0x00, 0x96, 0x42, 0x44, 0x2f, 0x0b, 0x2f, 0x03, 0x48, 0x78, 0x00, 0x01, 0x48, 0x78, 0x00, 0x01, 0x2f, 0x02, 0x4e, 0xba, 0xfc, 0x6e, 0x30, 0x00,
	0x4f, 0xef, 0x00, 0x14, 0x66, 0x00, 0x00, 0x28, 0x2f, 0x2e, 0xff, 0xfc, 0x2f, 0x03, 0x48, 0x78, 0x00, 0x01, 0x42, 0xa7, 0x2f, 0x02, 0x4e, 0xba, 0xfc, 0x52, 0x30, 0x00, 0x4f, 0xef, 0x00, 0x14,
	0x66, 0x00, 0x00, 0x0c, 0x52, 0x44, 0x0c, 0x44, 0x00, 0x0a, 0x6c, 0x52, 0x60, 0xbe, 0x52, 0x6e, 0xff, 0xfa, 0x0c, 0x6e, 0x00, 0x02, 0xff, 0xfa, 0x6e, 0x00, 0x00, 0x44, 0x2f, 0x03, 0x2f, 0x02,
	0x4e, 0xba, 0x00, 0x56, 0x50, 0x8f, 0x2f, 0x0b, 0x2f, 0x03, 0x48, 0x78, 0x00, 0x01, 0x48, 0x78, 0x00, 0x01, 0x2f, 0x02, 0x4e, 0xba, 0xfc, 0x14, 0x30, 0x00, 0x4f, 0xef, 0x00, 0x14, 0x66, 0x00,
	0x00, 0x1e, 0x2f, 0x2e, 0xff, 0xfc, 0x2f, 0x03, 0x48, 0x78, 0x00, 0x01, 0x42, 0xa7, 0x2f, 0x02, 0x4e, 0xba, 0xfb, 0xf8, 0x30, 0x00, 0x4f, 0xef, 0x00, 0x14, 0x66, 0x00, 0xff, 0x06, 0x2f, 0x0a,
	0x4e, 0xba, 0x01, 0xa0, 0x2f, 0x2e, 0xff, 0xf6, 0x4e, 0xba, 0x01, 0x74, 0x50, 0x8f, 0x4c, 0xee, 0x0c, 0x7c, 0xff, 0xd8, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xd4, 0x48, 0xe7, 0x30, 0x00,
	0x34, 0x2e, 0x00, 0x0a, 0x26, 0x2e, 0x00, 0x0c, 0x48, 0x78, 0x00, 0x06, 0x48, 0x78, 0x00, 0x07, 0x48, 0x6e, 0xff, 0xde, 0x4e, 0xba, 0x00, 0xaa, 0x48, 0x78, 0x00, 0x08, 0x42, 0xa7, 0x48, 0x6e,
	0xff, 0xd6, 0x4e, 0xba, 0x00, 0x9c, 0x1d, 0x7c, 0x00, 0x04, 0xff, 0xd9, 0x3d, 0x7c, 0x00, 0x02, 0xff, 0xec, 0x41, 0xee, 0xff, 0xd6, 0x2d, 0x48, 0xff, 0xee, 0x70, 0x08, 0x2d, 0x40, 0xff, 0xf2,
	0x3d, 0x7c, 0x00, 0x07, 0xff, 0xf6, 0x41, 0xee, 0xff, 0xda, 0x20, 0x83, 0x48, 0x78, 0x0e, 0x10, 0x42, 0xa7, 0x48, 0x78, 0x00, 0x01, 0x48, 0x6e, 0xff, 0xec, 0x30, 0x02, 0x48, 0xc0, 0x2f, 0x00,
	0x48, 0x78, 0x00, 0x06, 0x48, 0x6e, 0xff, 0xde, 0x4e, 0xba, 0xfc, 0x8e, 0x4a, 0x80, 0x4f, 0xef, 0x00, 0x34, 0x67, 0x26, 0x48, 0x78, 0x00, 0x08, 0x48, 0x6e, 0xff, 0xe4, 0x30, 0x02, 0x48, 0xc0,
	0x2f, 0x00, 0x4e, 0xba, 0xfd, 0x88, 0x4a, 0x80, 0x4f, 0xef, 0x00, 0x0c, 0x67, 0x04, 0x70, 0xff, 0x60, 0x0a, 0x70, 0x00, 0x10, 0x2e, 0xff, 0xe6, 0x60, 0x02, 0x70, 0x00, 0x4c, 0xee, 0x00, 0x0c,
	0xff, 0xcc, 0x4e, 0x5e, 0x4e, 0x75, 0x20, 0x6f, 0x00, 0x04, 0x22, 0x6f, 0x00, 0x08, 0x20, 0x2f, 0x00, 0x0c, 0x60, 0x04, 0x10, 0xd9, 0x53, 0x80, 0x4a, 0x80, 0x66, 0x00, 0xff, 0xf8, 0x4e, 0x75,
	0x22, 0x6f, 0x00, 0x04, 0x10, 0x2f, 0x00, 0x0b, 0x32, 0x2f, 0x00, 0x0e, 0x48, 0xc1, 0x60, 0x06, 0x20, 0x41, 0xd1, 0xc9, 0x42, 0x10, 0x53, 0x81, 0x4a, 0x81, 0x6c, 0x00, 0xff, 0xf4, 0x12, 0x80,
	0x4e, 0x75, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x01, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x02, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x03, 0x2f, 0x08, 0xac, 0x15,
	0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x04, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x05, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x06, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f,
	0x3f, 0x3c, 0x00, 0x08, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x09, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x5f, 0x3f, 0x3c, 0x00, 0x0a, 0x2f, 0x08, 0xac, 0x15, 0x20, 0x6f, 0x00, 0x0c,
	0x30, 0x2f, 0x00, 0x0a, 0x48, 0x40, 0x30, 0x2f, 0x00, 0x06, 0xa0, 0x4e, 0x4e, 0x75, 0x70, 0x00, 0x31, 0xc0, 0x02, 0x20, 0x20, 0x08, 0x4e, 0x75, 0xa1, 0x1a, 0x4e, 0xfa, 0xff, 0xf4, 0x20, 0x6f,
	0x00, 0x04, 0xa0, 0x1b, 0x4e, 0xfa, 0xff, 0xea, 0x20, 0x78, 0x02, 0xa6, 0x4e, 0xfa, 0xff, 0xe0, 0x20, 0x78, 0x02, 0xaa, 0x4e, 0xfa, 0xff, 0xd8, 0x20, 0x2f, 0x00, 0x04, 0xa1, 0x22, 0x4e, 0xfa,
	0xff, 0xd0, 0x20, 0x6f, 0x00, 0x04, 0xa0, 0x23, 0x4e, 0xfa, 0xff, 0xc6, 0x20, 0x6f, 0x00, 0x04, 0xa0, 0x29, 0x4e, 0xfa, 0xff, 0xbc, 0x30, 0x6f, 0x00, 0x06, 0x20, 0x2f, 0x00, 0x08, 0xa0, 0x2f,
	0x48, 0xc0, 0x4e, 0x75, 0x22, 0x6f, 0x00, 0x08, 0x20, 0x6f, 0x00, 0x04, 0x2f, 0x02, 0xa9, 0x6e, 0x24, 0x1f, 0x48, 0xc0, 0x4e, 0x75, 0x30, 0x2f, 0x00, 0x06, 0x12, 0x2f, 0x00, 0x0b, 0x4a, 0x01,
	0x67, 0x04, 0xa7, 0x46, 0x60, 0x02, 0xa3, 0x46, 0x20, 0x08, 0x4e, 0x75, 0x20, 0x6f, 0x00, 0x04, 0xa0, 0x33, 0x48, 0xc0, 0x4e, 0x75, 0x20, 0x6f, 0x00, 0x04, 0xa0, 0x34, 0x48, 0xc0, 0x4e, 0x75,
	0x4e, 0xba, 0x00, 0x58, 0x06, 0x80, 0x00, 0x00, 0x00, 0x20, 0x4e, 0x75, 0x2f, 0x0d, 0x20, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x66, 0x0c, 0x20, 0x6f, 0x00, 0x08, 0x70, 0x07, 0x20, 0xdd, 0x51, 0xc8,
	0xff, 0xfc, 0x2a, 0x6f, 0x00, 0x08, 0x4e, 0xba, 0x00, 0x3a, 0x2a, 0x5f, 0x4e, 0x75, 0x20, 0x0d, 0x2a, 0x6f, 0x00, 0x04, 0x4e, 0x75, 0x2a, 0x6f, 0x00, 0x04, 0x4e, 0x75, 0x4e, 0xba, 0xff, 0xc2,
	0xa1, 0x1e, 0x2f, 0x08, 0x4e, 0xba, 0x00, 0x14, 0xd0, 0x9f, 0x4e, 0x75, 0x4e, 0xba, 0x00, 0x0c, 0x20, 0x6f, 0x00, 0x04, 0x91, 0xc0, 0xa0, 0x1f, 0x4e, 0x75, 0x41, 0xfa, 0x00, 0xce, 0x20, 0x10,
	0x4e, 0x75, 0x48, 0xe7, 0xff, 0xf0, 0x42, 0x47, 0x41, 0xfa, 0x00, 0xc0, 0x22, 0x18, 0x6f, 0x00, 0x00, 0xa6, 0x2a, 0x18, 0x66, 0x04, 0x2a, 0x0d, 0x9a, 0x81, 0x26, 0x45, 0x24, 0x4b, 0xe2, 0x81,
	0x60, 0x02, 0x42, 0x5a, 0x51, 0xc9, 0xff, 0xfc, 0x30, 0x18, 0x3e, 0x18, 0x60, 0x00, 0x00, 0x84, 0x78, 0x00, 0x18, 0x18, 0x22, 0x04, 0x02, 0x01, 0x00, 0x0f, 0x08, 0x04, 0x00, 0x04, 0x67, 0x0e,
	0xe1, 0x41, 0x12, 0x18, 0x08, 0x81, 0x00, 0x0b, 0x67, 0x04, 0xe1, 0x81, 0x12, 0x18, 0x74, 0x01, 0x08, 0x04, 0x00, 0x07, 0x67, 0x16, 0x14, 0x18, 0x08, 0x82, 0x00, 0x07, 0x67, 0x0e, 0xe1, 0x42,
	0x14, 0x18, 0x08, 0x82, 0x00, 0x0e, 0x67, 0x04, 0xe1, 0x82, 0x14, 0x18, 0x7c, 0x02, 0x4e, 0xba, 0x00, 0x4c, 0x08, 0x85, 0x00, 0x0f, 0x67, 0x04, 0xe1, 0x85, 0x1a, 0x18, 0x43, 0xf3, 0x58, 0x00,
	0x24, 0x49, 0x08, 0x04, 0x00, 0x05, 0x67, 0x1c, 0x2c, 0x01, 0x4e, 0xba, 0x00, 0x30, 0x0c, 0x41, 0x00, 0x02, 0x67, 0x06, 0x6d, 0x08, 0xdb, 0x92, 0x60, 0x0e, 0xdb, 0x52, 0x60, 0x0a, 0xdb, 0x12,
	0x60, 0x06, 0x12, 0xd8, 0x51, 0xc9, 0xff, 0xfc, 0x08, 0x04, 0x00, 0x06, 0x67, 0x04, 0x26, 0x0d, 0xd7, 0x92, 0x51, 0xc8, 0xff, 0x7c, 0x4c, 0xdf, 0x0f, 0xff, 0x4e, 0x75, 0x7a, 0x00, 0x60, 0x04,
	0xe1, 0x8d, 0x1a, 0x18, 0x51, 0xce, 0xff, 0xfa, 0x4e, 0x75, 0x00, 0x00, 0x03, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x8a, 0x25, 0x41, 0x35, 0x69, 0x80, 0x00,
	0x03, 0x7e, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x19, 0x1a, 0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x69, 0x6e, 0x67, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x53, 0x43, 0x53, 0x49, 0x20, 0x64, 0x72, 0x69, 0x76,
	0x65, 0x73, 0x2e, 0x2c, 0x49, 0x6e, 0x69, 0x74, 0x69, 0x61, 0x6c, 0x69, 0x7a, 0x69, 0x6e, 0x67, 0x20, 0x64, 0x69, 0x73, 0x6b, 0x2e, 0x2e, 0x2e, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x74,
	0x69, 0x6e, 0x67, 0x20, 0x69, 0x6e, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x65, 0x73, 0x73, 0x2e, 0x20, 0x55, 0x70, 0x64, 0x61, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x64, 0x72, 0x69, 0x76, 0x65, 0x72,
};

}

int main(int argc, char *argv[]) {
	// Announce failure if appropriate arguments weren't given.
	if(argc != 3) {
		std::cout << "USAGE: scsimanagerregress input output" << std::endl << std::endl;
		std::cout << "This tool modifies a classic Macintosh volume image, replacing its built-in driver with a SCSI driver compatible with early 68k-based machines." << std::endl;
		return EXIT_FAILURE;
	}

	using File = std::unique_ptr<FILE, int (*)(FILE *)>;
	File source(fopen(argv[1], "rb"), fclose);				// This is a C++11 project; there's no make_unique.
	if(!source) {
		std::cout << "Unable to open " << argv[1] << " for input" << std::endl;
		return EXIT_FAILURE;
	}

	// Read the driver descriptor and the first entry in the partition map.
	std::vector<uint8_t> volume_map(1024);
	fread(volume_map.data(), 512, 2, source.get());
	
	// Check for the proper device signature.
	if(volume_map[0] != 'E' || volume_map[1] != 'R') {
		std::cout << argv[1] << " doesn't appear to be a device image." << std::endl;
		return EXIT_FAILURE;
	}

	// Hence learn how many partitions there are in total, and read in the other map entries.
	//
	// Quick bluffer's guide: blocks are 512 bytes; the first contains a driver descriptor and
	// the next n are one block per partition map entry. The total number of partition map entries
	// is stored at offset 7 in every entry.
	const uint8_t partition_count = volume_map[512 + 7];
	volume_map.resize((partition_count+1) * 512);
	fread(&volume_map[1024], 512, partition_count - 1, source.get());

	// Check that all apparent partition map entries have the proper signatures,
	// provide some user feedback, and look for the driver partition.
	uint8_t *driver_partition = nullptr;
	std::cout << "Partitions:" << std::endl;
	for(uint8_t c = 0; c < partition_count; c++) {
		uint8_t *const partition = &volume_map[(c+1)*512];
		
		if(partition[0] != 'P' || partition[1] != 'M') {
			std::cout << "Unable to parse partition map." << std::endl;
			return EXIT_FAILURE;
		}

		std::string name(&partition[16], &partition[48]);
		std::string type(&partition[48], &partition[64]);
		std::cout << "\t" << name << "; type: " << type << std::endl;
		
		if(!type.rfind("Apple_Driver")) {
			driver_partition = partition;
		}
	}

	if(!driver_partition) {
		std::cout << "No existing driver partition found." << std::endl;
	}

#define be32(x) ntohl(*reinterpret_cast<uint32_t *>(&x))

	// Check that the existing driver partition is long enough to fit the
	// replacement driver.
	const uint32_t driver_block_size = (sizeof(driver) + 511) / 512;
	const uint32_t driver_partition_size = be32(driver_partition[12]);
	if(driver_partition_size < driver_block_size) {
		std::cout << "Driver partition not large enough; hassle me to improve this tool." << std::endl;
	}

	// Open the output.
	File destination(fopen(argv[2], "wb"), fclose);
	if(!destination) {
		std::cout << "Unable to open " << argv[2] << " for output" << std::endl;
		return EXIT_FAILURE;
	}

	// Modify the driver partition map entry.
	
	// Shorten the type name if necessary.
	const size_t type_length = strlen("Apple_Driver");
	memset(&driver_partition[48 + type_length], 0, 16 - type_length);

	// This version of the driver code is 0x139e bytes long.
	driver_partition[98] = 0x13;
	driver_partition[99] = 0x9e;

	// The driver has a checksum of 0x84b9.
	driver_partition[118] = 0x84;
	driver_partition[119] = 0xb9;	

	// The driver is for the 68000.
	memcpy(&driver_partition[120], "68000", strlen("68000"));

	// The following values are all written by the Apple HD SC Tool to
	// reserved fields. I don't know what they mean.
	driver_partition[137] = 0x01;
	driver_partition[138] = 0x06;
	driver_partition[143] = 0x01;
	driver_partition[147] = 0x02;
	driver_partition[149] = 0x07;

	// Write out the modified volume map.
	fwrite(volume_map.data(), 1, volume_map.size(), destination.get());

	// Copy input to output as far as the beginning of the driver partition.
	const uint32_t driver_partition_location = be32(driver_partition[8]);
	for(int c = partition_count + 1; c < driver_partition_location; c++) {
		uint8_t block[512];
		fread(block, 512, 1, source.get());
		fwrite(block, 512, 1, destination.get());
	}

	// Write the driver included in this source file, and pad out to
	// the specified driver size.
	fwrite(driver, 1, sizeof(driver), destination.get());
	fseek(source.get(), driver_block_size * 512 - sizeof(driver), SEEK_CUR);
	
	// Skip the original driver.
	fseek(source.get(), driver_block_size * 512, SEEK_CUR);

	// Copy everything remaining from source to dest.
	while(true) {
		uint8_t block[512];
		fread(block, 512, 1, source.get());
		if(feof(source.get())) break;
		fwrite(block, 512, 1, destination.get());
	}

	return EXIT_SUCCESS;
}
/* SPDX-License-Identifier: GPL-2.0+ OR Apache-2.0 */
/*
 * Copyright (C) 2018-2019 HUAWEI, Inc.
 *             http://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#ifndef __EROFS_LIB_COMPRESSOR_H
#define __EROFS_LIB_COMPRESSOR_H

#include "erofs/defs.h"

struct erofs_compress;

struct erofs_compressor {
	int default_level;
	int best_level;

	int (*init)(struct erofs_compress *c);
	int (*exit)(struct erofs_compress *c);
	int (*setlevel)(struct erofs_compress *c, int compression_level);

	int (*compress_destsize)(const struct erofs_compress *c,
				 const void *src, unsigned int *srcsize,
				 void *dst, unsigned int dstsize);
};

struct erofs_algorithm {
	char *name;
	const struct erofs_compressor *c;
	unsigned int id;

	/* its name won't be shown as a supported algorithm */
	bool optimisor;
};

struct erofs_compress {
	struct erofs_sb_info *sbi;
	const struct erofs_algorithm *alg;

	unsigned int compress_threshold;
	unsigned int compression_level;

	void *private_data;
};

/* list of compression algorithms */
extern const struct erofs_compressor erofs_compressor_lz4;
extern const struct erofs_compressor erofs_compressor_lz4hc;
extern const struct erofs_compressor erofs_compressor_lzma;
extern const struct erofs_compressor erofs_compressor_deflate;
extern const struct erofs_compressor erofs_compressor_libdeflate;

int z_erofs_get_compress_algorithm_id(const struct erofs_compress *c);
int erofs_compress_destsize(const struct erofs_compress *c,
			    const void *src, unsigned int *srcsize,
			    void *dst, unsigned int dstsize);

int erofs_compressor_setlevel(struct erofs_compress *c, int compression_level);
int erofs_compressor_init(struct erofs_sb_info *sbi,
		struct erofs_compress *c, char *alg_name);
int erofs_compressor_exit(struct erofs_compress *c);

#endif

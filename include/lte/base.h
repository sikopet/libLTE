/*
 * Copyright (c) 2013, Ismael Gomez-Miguelez <gomezi@tcd.ie>.
 * This file is part of OSLD-lib (http://https://github.com/ismagom/osld-lib)
 *
 * OSLD-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OSLD-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OSLD-lib.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LTEBASE_
#define _LTEBASE_

#define NSUBFRAMES_X_FRAME	10
#define NSLOTS_X_FRAME (2*NSUBFRAMES_X_FRAME)

#define MAX_PORTS	4

typedef enum {CPNORM, CPEXT} lte_cp_t;

#define MAX_NSYMB		7

#define CPNORM_NSYMB	7
#define CPNORM_SF_NSYMB	2*CPNORM_NSYMB
#define CPNORM_0_LEN	160
#define CPNORM_LEN		144

#define CPEXT_NSYMB		6
#define CPEXT_SF_NSYMB	2*CPEXT_NSYMB
#define CPEXT_LEN		512
#define CPEXT_7_5_LEN	1024

#define CP_ISNORM(cp) (cp==CPNORM)
#define CP_ISEXT(cp) (cp==CPEXT)
#define CP_NSYMB(cp) (CP_ISNORM(cp)?CPNORM_NSYMB:CPEXT_NSYMB)

#define CP(symbol_sz, c) (c*symbol_sz/2048)
#define CP_NORM(symbol, symbol_sz) (symbol==0)?CP(symbol_sz,CPNORM_0_LEN):CP(symbol_sz,CPNORM_LEN)
#define CP_EXT(symbol_sz) CP(symbol_sz,CPEXT_LEN)

#define SLOT_LEN_CPNORM(symbol_sz) (symbol_sz+CP(symbol_sz,CPNORM_0_LEN)+(CPNORM_NSYMB-1)*(symbol_sz+CP(symbol_sz,CPNORM_LEN)))
#define SLOT_LEN_CPEXT(symbol_sz) (CPEXT_NSYMB*(symbol_sz+CP(symbol_sz, CPEXT_LEN)))

#define SF_LEN_CPNORM(symbol_sz) 2*SLOT_LEN_CPNORM(symbol_sz)
#define SF_LEN_CPEXT(symbol_sz) 2*SLOT_LEN_CPEXT(symbol_sz)

#define SF_IDX_CPNORM(idx, symbol_sz) (idx==0?(CP(symbol_sz, CPNORM_0_LEN)):(CP(symbol_sz, CPNORM_0_LEN)+idx*(symbol_sz+CP(symbol_sz, CPNORM_LEN))))
#define SF_IDX_CPEXT(idx, symbol_sz) (idx*(symbol_sz+CP(symbol_sz, CPEXT_LEN)))

#define SLOT_IDX_CPNORM(idx, symbol_sz) (idx==0?0:symbol_sz*CPNORM_NSYMB)
#define SLOT_IDX_CPEXT(idx, symbol_sz) (idx==0?0:symbol_sz*CPEXT_NSYMB)

#define MAX_PRB		110
#define RE_X_RB		12

#define RS_VSHIFT(cell_id) (cell_id%6)

#define GUARD_RE(nof_prb)	((lte_symbol_sz(nof_prb)-nof_prb*RE_X_RB)/2)

#define SAMPLE_IDX(nof_prb, symbol_idx, sample_idx) (symbol_idx*nof_prb*RE_X_RB + sample_idx)

const int lte_symbol_sz(int nof_prb);
int lte_re_x_prb(int ns, int symbol, int nof_ports, int nof_symbols);
int lte_voffset(int symbol_id, int cell_id, int nof_ports);

#define NOF_LTE_BANDS	29


typedef struct {
	int id;
	float fd;
}lte_earfcn_t;

enum band_geographical_area {
	ALL, NAR, APAC, EMEA, JAPAN, CALA, NA
};

float lte_band_fd(int earfcn);
int lte_band_get_fd_band(int band, lte_earfcn_t *earfcn, int earfcn_start, int earfcn_end, int max_elems);
int lte_band_get_fd_band_all(int band, lte_earfcn_t *earfcn, int max_nelems);
int lte_band_get_fd_region(enum band_geographical_area region, lte_earfcn_t *earfcn, int max_elems);



#endif

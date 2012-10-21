/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: check.h 1970 2010-11-20 11:27:06Z ertl-hiro $
 */

/*
 *		エラーチェック用マクロ
 */

#ifndef TOPPERS_CHECK_H
#define TOPPERS_CHECK_H

/*
 *  予約属性エラーのチェック（E_PAR）
 */
#define CHECK_RSATR(atr, valid_atr) {						\
	if (((atr) & ~(valid_atr)) != 0U) {						\
		ercd = E_RSATR;										\
		goto error_exit;									\
	}														\
}

/*
 *  優先度の範囲の判定
 */
#define VALID_TPRI(tpri)	(TMIN_TPRI <= (tpri) && (tpri) <= TMAX_TPRI)

#define VALID_DPRI(dpri)	(TMIN_DPRI <= (dpri) && (dpri) <= TMAX_DPRI)

#define VALID_MPRI(mpri)	(TMIN_MPRI <= (mpri) && (mpri) <= TMAX_MPRI)

#define VALID_ISRPRI(isrpri) \
				(TMIN_ISRPRI <= (isrpri) && (isrpri) <= TMAX_ISRPRI)

#ifndef VALID_INTPRI_CHGIPM
#define VALID_INTPRI_CHGIPM(intpri) \
				(TMIN_INTPRI <= (intpri) && (intpri) <= TIPM_ENAALL)
#endif /* VALID_INTPRI_CHGIPM */

/*
 *  タスク優先度のチェック（E_PAR）
 */
#define CHECK_TPRI(tpri) {									\
	if (!VALID_TPRI(tpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_TPRI_INI(tpri) {								\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_INI)) {		\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_TPRI_SELF(tpri) {								\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_SELF)) {		\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  データ優先度のチェック（E_PAR）
 */
#define CHECK_DPRI(dpri) {									\
	if (!VALID_DPRI(dpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  メッセージ優先度のチェック（E_PAR）
 */
#define CHECK_MPRI(mpri) {									\
	if (!VALID_MPRI(mpri)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  割込みサービスルーチン優先度のチェック（E_PAR）
 */
#define CHECK_ISRPRI(isrpri) {								\
	if (!VALID_ISRPRI(isrpri)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  タイムアウト指定値のチェック（E_PAR）
 */
#define CHECK_TMOUT(tmout) {								\
	if (!(TMO_FEVR <= (tmout))) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  割込み優先度のチェック（E_PAR）
 */
#define CHECK_INTPRI_CHGIPM(intpri) {						\
	if (!VALID_INTPRI_CHGIPM(intpri)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  割込み番号のチェック（E_PAR）
 */
#define CHECK_INTNO_CREISR(intno) {							\
	if (!VALID_INTNO_CREISR(intno)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_INTNO_DISINT(intno) {							\
	if (!VALID_INTNO_DISINT(intno)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  アラインしているかの判定
 */
#define ALIGNED(val, align)		((((uintptr_t)(val)) & ((align) - 1U)) == 0U)

#ifdef CHECK_FUNC_ALIGN
#define FUNC_ALIGNED(func)		ALIGNED(func, CHECK_FUNC_ALIGN)
#else /* CHECK_FUNC_ALIGN */
#define FUNC_ALIGNED(func)		true
#endif /* CHECK_FUNC_ALIGN */

#ifdef CHECK_STKSZ_ALIGN
#define STKSZ_ALIGNED(stksz)	ALIGNED(stksz, CHECK_STKSZ_ALIGN)
#else /* CHECK_STKSZ_ALIGN */
#define STKSZ_ALIGNED(stksz)	true
#endif /* CHECK_STKSZ_ALIGN */

#ifdef CHECK_STACK_ALIGN
#define STACK_ALIGNED(stack)	ALIGNED(stack, CHECK_STACK_ALIGN)
#else /* CHECK_STACK_ALIGN */
#define STACK_ALIGNED(stack)	true
#endif /* CHECK_STACK_ALIGN */

#ifdef CHECK_MPF_ALIGN
#define MPF_ALIGNED(mpf)		ALIGNED(mpf, CHECK_MPF_ALIGN)
#else /* CHECK_MPF_ALIGN */
#define MPF_ALIGNED(mpf)		true
#endif /* CHECK_MPF_ALIGN */

#ifdef CHECK_MB_ALIGN
#define MB_ALIGNED(mb)			ALIGNED(mb, CHECK_MB_ALIGN)
#else /* CHECK_MB_ALIGN */
#define MB_ALIGNED(mb)			true
#endif /* CHECK_MB_ALIGN */

/*
 *  NULLでないことのチェック
 */
#ifdef CHECK_FUNC_NONNULL
#define FUNC_NONNULL(func)		((func) != NULL)
#else /* CHECK_FUNC_NONNULL */
#define FUNC_NONNULL(func)		true
#endif /* CHECK_FUNC_NONNULL */

#ifdef CHECK_STACK_NONNULL
#define STACK_NONNULL(stack)	((stack) != NULL)
#else /* CHECK_STACK_NONNULL */
#define STACK_NONNULL(stack)	true
#endif /* CHECK_STACK_NONNULL */

#ifdef CHECK_MPF_NONNULL
#define MPF_NONNULL(mpf)		((mpf) != NULL)
#else /* CHECK_MPF_NONNULL */
#define MPF_NONNULL(mpf)		true
#endif /* CHECK_MPF_NONNULL */

/*
 *  関数の先頭番地のチェック（E_PAR）
 */
#define CHECK_ALIGN_FUNC(func) {							\
	if (!FUNC_ALIGNED(func)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_NONNULL_FUNC(func) {							\
	if (!FUNC_NONNULL(func)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  スタックサイズのチェック（E_PAR）
 */
#define CHECK_ALIGN_STKSZ(stksz) {							\
	if (!STKSZ_ALIGNED(stksz)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#ifndef TARGET_MIN_STKSZ
#define TARGET_MIN_STKSZ	1U		/* 未定義の場合は0でないことをチェック */
#endif /* TARGET_MIN_STKSZ */

#define CHECK_STKSZ_MIN(stksz) {							\
	if ((stksz) < TARGET_MIN_STKSZ) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  スタックの先頭番地のチェック（E_PAR）
 */
#define CHECK_ALIGN_STACK(stack) {							\
	if (!STACK_ALIGNED(stack)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_NONNULL_STACK(stack) {						\
	if (!STACK_NONNULL(stack)) {							\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  固定長メモリプール領域の先頭番地のチェック（E_PAR）
 */
#define CHECK_ALIGN_MPF(mpf) {								\
	if (!MPF_ALIGNED(mpf)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

#define CHECK_NONNULL_MPF(mpf) {							\
	if (!MPF_NONNULL(mpf)) {								\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  管理領域の先頭番地のチェック（E_PAR）
 */
#define CHECK_ALIGN_MB(mb) {								\
	if (!MB_ALIGNED(mb)) {									\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  その他のパラメータエラーのチェック（E_PAR）
 */
#define CHECK_PAR(exp) {									\
	if (!(exp)) {											\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
}

/*
 *  オブジェクトIDの範囲の判定
 */
#define VALID_TSKID(tskid)	(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)
#define VALID_SEMID(semid)	(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)
#define VALID_FLGID(flgid)	(TMIN_FLGID <= (flgid) && (flgid) <= tmax_flgid)
#define VALID_DTQID(dtqid)	(TMIN_DTQID <= (dtqid) && (dtqid) <= tmax_dtqid)
#define VALID_PDQID(pdqid)	(TMIN_PDQID <= (pdqid) && (pdqid) <= tmax_pdqid)
#define VALID_MBXID(mbxid)	(TMIN_MBXID <= (mbxid) && (mbxid) <= tmax_mbxid)
#define VALID_MPFID(mpfid)	(TMIN_MPFID <= (mpfid) && (mpfid) <= tmax_mpfid)
#define VALID_CYCID(cycid)	(TMIN_CYCID <= (cycid) && (cycid) <= tmax_cycid)
#define VALID_ALMID(almid)	(TMIN_ALMID <= (almid) && (almid) <= tmax_almid)
#define VALID_ISRID(isrid)	(TMIN_ISRID <= (isrid) && (isrid) <= tmax_isrid)

/*
 *  オブジェクトIDのチェック（E_ID）
 */
#define CHECK_TSKID(tskid) {								\
	if (!VALID_TSKID(tskid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_TSKID_SELF(tskid) {							\
	if (!(VALID_TSKID(tskid) || (tskid) == TSK_SELF)) {		\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_SEMID(semid) {								\
	if (!VALID_SEMID(semid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_FLGID(flgid) {								\
	if (!VALID_FLGID(flgid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_DTQID(dtqid) {								\
	if (!VALID_DTQID(dtqid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_PDQID(pdqid) {								\
	if (!VALID_PDQID(pdqid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_MBXID(mbxid) {								\
	if (!VALID_MBXID(mbxid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_MPFID(mpfid) {								\
	if (!VALID_MPFID(mpfid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_CYCID(cycid) {								\
	if (!VALID_CYCID(cycid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_ALMID(almid) {								\
	if (!VALID_ALMID(almid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

#define CHECK_ISRID(isrid) {								\
	if (!VALID_ISRID(isrid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
}

/*
 *  呼出しコンテキストのチェック（E_CTX）
 */
#define CHECK_TSKCTX() {									\
	if (sense_context()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

#define CHECK_INTCTX() {									\
	if (!sense_context()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

/*
 *  呼出しコンテキストとCPUロック状態のチェック（E_CTX）
 */
#define CHECK_TSKCTX_UNL() {								\
	if (sense_context() || t_sense_lock()) {				\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

#define CHECK_INTCTX_UNL() {								\
	if (!sense_context() || i_sense_lock()) {				\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

/*
 *  ディスパッチ保留状態でないかのチェック（E_CTX）
 */
#define CHECK_DISPATCH() {									\
	if (sense_context() || t_sense_lock() || !dspflg) {		\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

/*
 *  その他のコンテキストエラーのチェック（E_CTX）
 */
#define CHECK_CTX(exp) {									\
	if (!(exp)) {											\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
}

/*
 *  自タスクを指定していないかのチェック（E_ILUSE）
 */
#define CHECK_NONSELF(p_tcb) {								\
	if ((p_tcb) == p_runtsk) {								\
		ercd = E_ILUSE;										\
		goto error_exit;									\
	}														\
}

/*
 *  その他の不正使用エラーのチェック（E_ILUSE）
 */
#define CHECK_ILUSE(exp) {									\
	if (!(exp)) {											\
		ercd = E_ILUSE;										\
		goto error_exit;									\
	}														\
}

/*
 *  未サポート機能エラーのチェック（E_NOSPT）
 */
#define CHECK_NOSPT(exp) {									\
	if (!(exp)) {											\
		ercd = E_NOSPT;										\
		goto error_exit;									\
	}														\
}

#endif /* TOPPERS_CHECK_H */

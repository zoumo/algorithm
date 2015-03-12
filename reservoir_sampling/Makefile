#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -O2 \
  -finline-functions \
  -pipe \
  -W \
  -Wall \
  -Wreorder \
  -Weffc++ \
  -Wwrite-strings \
  -Wswitch \
  -Wpointer-arith \
  -Wconversion \
  -Wsign-promo \
  -Wredundant-decls \
  -DNDEBUG
CFLAGS=-g \
  -O2 \
  -pipe \
  -W \
  -Wall
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.0.0.0\"
INCPATH=-I. \
  -I./include \
  -I./output \
  -I./output/include
DEP_INCPATH=-I../lib-64/utllib \
  -I../lib-64/utllib/include \
  -I../lib-64/utllib/output \
  -I../lib-64/utllib/output/include \
  -I../third-64/gflags \
  -I../third-64/gflags/include \
  -I../third-64/gflags/output \
  -I../third-64/gflags/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=89a5d3a9ea7206b778ffce9049e99aa8  COMAKE


.PHONY:all
all:comake2_makefile_check reservoir_sampling 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf reservoir_sampling
	rm -rf ./output/bin/reservoir_sampling
	rm -rf reservoir_sampling_reservoir_sampling.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

reservoir_sampling:reservoir_sampling_reservoir_sampling.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mreservoir_sampling[0m']"
	$(CXX) reservoir_sampling_reservoir_sampling.o -Xlinker "-("  ../third-64/gflags/lib/libgflags.a \
  ../third-64/gflags/lib/libgflags_nothreads.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o reservoir_sampling
	mkdir -p ./output/bin
	cp -f --link reservoir_sampling ./output/bin

reservoir_sampling_reservoir_sampling.o:reservoir_sampling.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mreservoir_sampling_reservoir_sampling.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o reservoir_sampling_reservoir_sampling.o reservoir_sampling.cpp

endif #ifeq ($(shell uname -m),x86_64)



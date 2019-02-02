define $(_flavor_)_$(_feat_)_MAKE
 
$(_flavor_)_$(_feat_)_inc=\
ccbarrier.h \
cccond_var.h \
ccdispatcher.h \
ccfactory.h \
ccipc.h \
ccmail.h \
ccmailbox.h \
ccmutex.h \
ccnode.h \
ccpublisher.h \
ccsemaphore.h \
ccthread.h \
ccworker.h \
ccworker_mailist.h \

$(_flavor_)_$(_feat_)_lib_objs=\
ccthread \
ccmail \
ccmailbox \
ccpublisher \
#ccdispatcher \
ccipc \
ccworker \

$(_flavor_)_$(_feat_)_lib=ccipc

endef

include $(PROJ_MAK_DIR)/epilog.mk

define $(_flavor_)_$(_feat_)_MAKE
 
$(_flavor_)_$(_feat_)_inc=\
ccbarrier.h \
ccbundle.h \
cccond_var.h \
ccdispatcher.h \
ccfactory.h \
ccipc.h \
ccmail.h \
ccmailbox.h \
ccmutex.h \
ccpublisher.h \
ccrw_lock.h \
ccsemaphore.h \
ccthread.h \
ccworker.h \
ccworker_mailist.h \

$(_flavor_)_$(_feat_)_lib_objs=\
ccthread \
ccmail \
ccmailbox \
ccpublisher \
ccworker \
ccipc \

$(_flavor_)_$(_feat_)_lib=ccipc

endef

include $(PROJ_MAK_DIR)/epilog.mk

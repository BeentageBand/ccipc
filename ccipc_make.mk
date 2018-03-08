define $(_flavor_)_$(_feat_)_MAKE
 
$(_flavor_)_$(_feat_)_inc=\
ccdispatcher.h \
ccipc.h \
ccipc_types.h \
ccmail.h \
ccmailbox.h \
ccnode.h \
ccpublisher.h \
ccsubscribable.h \
ccthread.h \
ccworker.h \
ccworker_mailist.h \

$(_flavor_)_$(_feat_)_lib_objs=\
ccdispatcher \
ccipc \
ccmailbox \
ccpublisher \
ccthread \
ccworker \

$(_flavor_)_$(_feat_)_lib=ccipc

endef

include $(PROJ_MAK_DIR)/epilog.mk

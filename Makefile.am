 ACLOCAL_AMFLAGS = -I m4 --install
# Libraries
lib_LTLIBRARIES = libccipc-1.0.0.la
libccipc_1_0_0_la_SOURCES = \
ccipc/ccipc.cpp                   \
ccipc/ccipc.h                     \
ccipc/bundle/ccbundle.h           \
ccipc/bundle/ccdispatcher.h       \
ccipc/bundle/ccworker.cpp         \
ccipc/bundle/ccworker.h           \
ccipc/bundle/ccworker_mailist.h   \
ccipc/common/ipc_types.h          \
ccipc/factory/ccfactory.h         \
ccipc/mailbox/ccmailbox.cpp       \
ccipc/mailbox/ccmailbox.h         \
ccipc/mail/ccmail.cpp             \
ccipc/mail/ccmail.h               \
ccipc/publisher/ccpublisher.cpp   \
ccipc/publisher/ccpublisher.h     \
ccipc/sync/ccbarrier.h            \
ccipc/sync/cccond_var.h           \
ccipc/sync/ccmutex.h              \
ccipc/sync/ccrw_lock.h            \
ccipc/sync/ccsemaphore.h          \
ccipc/thread/ccthread.cpp         \
ccipc/thread/ccthread_sender.cpp  \
ccipc/thread/ccthread.h           \
ccipc/thread/ccthread_sender.h    

libccipc_1_0_0_la_LDFLAGS = -version-info 0:0:0
nobase_include_HEADERS = \
ccipc/ccipc.h                     \
ccipc/bundle/ccbundle.h           \
ccipc/bundle/ccdispatcher.h       \
ccipc/bundle/ccworker.h           \
ccipc/bundle/ccworker_mailist.h   \
ccipc/common/ipc_types.h          \
ccipc/factory/ccfactory.h         \
ccipc/mailbox/ccmailbox.h         \
ccipc/mail/ccmail.h               \
ccipc/publisher/ccpublisher.h     \
ccipc/sync/ccbarrier.h            \
ccipc/sync/cccond_var.h           \
ccipc/sync/ccmutex.h              \
ccipc/sync/ccrw_lock.h            \
ccipc/sync/ccsemaphore.h          \
ccipc/thread/ccthread.h           \
ccipc/thread/ccthread_sender.h    

pkgconfig_DATA = ccipc.pc

# Unit Tests
check_PROGRAMS = unittest
unittest_SOURCES = \
tst/ipc_gtests/ipc_factory_mock.h           \
tst/ipc_gtests/ipc_gtest.cpp                \
tst/ipc_gtests/ipc_mailbox_gtest.cpp        \
tst/ipc_gtests/ipc_mail_gtest.cpp           \
tst/ipc_gtests/ipc_publisher_gtest.cpp      \
tst/ipc_gtests/ipc_thread_gtest.cpp         \
tst/ipc_gtests/ipc_worker_gtest.cpp

unittest_CPPFLAGS = $(GMOCK_CFLAGS) $(CCIPC_CXXFLAGS)
unittest_LDADD = $(lib_LTLIBRARIES) $(GMOCK_LIBS) $(CCIPC_LIBS)
unittest_LDFLAGS = -no-install

EXTRA_DIST = m4/NOTES
dist_doc = README.md LICENSE

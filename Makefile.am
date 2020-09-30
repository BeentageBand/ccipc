 ACLOCAL_AMFLAGS = -I m4 --install
# Libraries
lib_LTLIBRARIES = libccipc-1.0.0.la
libccipc_1_0_0_la_SOURCES = \
ipc/ccipc.cpp                   \
ipc/ccipc.h                     \
ipc/bundle/ccbundle.h           \
ipc/bundle/ccdispatcher.h       \
ipc/bundle/ccworker.cpp         \
ipc/bundle/ccworker.h           \
ipc/bundle/ccworker_mailist.h   \
ipc/common/ipc_types.h          \
ipc/factory/ccfactory.h         \
ipc/mailbox/ccmailbox.cpp       \
ipc/mailbox/ccmailbox.h         \
ipc/mail/ccmail.cpp             \
ipc/mail/ccmail.h               \
ipc/publisher/ccpublisher.cpp   \
ipc/publisher/ccpublisher.h     \
ipc/sync/ccbarrier.h            \
ipc/sync/cccond_var.h           \
ipc/sync/ccmutex.h              \
ipc/sync/ccrw_lock.h            \
ipc/sync/ccsemaphore.h          \
ipc/thread/ccthread.cpp         \
ipc/thread/ccthread_sender.cpp  \
ipc/thread/ccthread.h           \
ipc/thread/ccthread_sender.h    

libccipc_1_0_0_la_LDFLAGS = -version-info 0:0:0
nobase_include_HEADERS = \
ipc/ccipc.h                     \
ipc/bundle/ccbundle.h           \
ipc/bundle/ccdispatcher.h       \
ipc/bundle/ccworker.h           \
ipc/bundle/ccworker_mailist.h   \
ipc/common/ipc_types.h          \
ipc/factory/ccfactory.h         \
ipc/mailbox/ccmailbox.h         \
ipc/mail/ccmail.h               \
ipc/publisher/ccpublisher.h     \
ipc/sync/ccbarrier.h            \
ipc/sync/cccond_var.h           \
ipc/sync/ccmutex.h              \
ipc/sync/ccrw_lock.h            \
ipc/sync/ccsemaphore.h          \
ipc/thread/ccthread.h           \
ipc/thread/ccthread_sender.h    

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
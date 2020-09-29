 ACLOCAL_AMFLAGS = -I m4 --install
# Libraries
lib_LTLIBRARIES = libccipc-1.0.0.la
libccipc_1_0_0_la_SOURCES = \
ccbarrier.h           \
cccond_var.h          \
ccfactory.h           \
ccipc.h               \
ccmailbox.h           \
ccmail.h              \
ccpublisher.cpp       \
ccrw_lock.h           \
ccthread.cpp          \
ccthread_sender.cpp   \
ccworker.cpp          \
ccworker_mailist.h    \
ccbundle.h            \
ccdispatcher.h        \
ccipc.cpp             \
ccmailbox.cpp         \
ccmail.cpp            \
ccmutex.h             \
ccpublisher.h         \
ccsemaphore.h         \
ccthread.h            \
ccthread_sender.h     \
ccworker.h            \
ipc_types.h

libccipc_1_0_0_la_LDFLAGS = -version-info 0:0:0
nobase_include_HEADERS = \
ccbarrier.h        \
cccond_var.h       \
ccfactory.h        \
ccmailbox.h        \
ccmutex.h          \
ccrw_lock.h        \
ccthread.h         \
ccworker.h         \
ccbundle.h         \
ccdispatcher.h     \
ccipc.h            \
ccmail.h           \
ccpublisher.h      \
ccsemaphore.h      \
ccthread_sender.h  \
ccworker_mailist.h \
ipc_types.h        

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
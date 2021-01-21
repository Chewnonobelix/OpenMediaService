#include "Model/library.h"
#include <QSignalSpy>
#include <QtTest>

// add necessary includes here

class LibraryTest : public QObject {
	Q_OBJECT
	Library model1, model2;
	QUuid id = QUuid::createUuid();
	QString name = "Name1";
	MediaPlayerGlobal::MediaRole role = MediaPlayerGlobal::MediaRole::Image;
	bool shared = true;
	QDateTime lastprobed = QDateTime::currentDateTime().addDays(-6);
	QString source = "Source1";
	QStringList sourceDir = QList<QString>({source});
	QString media = QStringLiteral(TESTDATA) + "/porte_d_eternite.jpg";

public:
	LibraryTest();
	~LibraryTest();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_id();
	void test_name();
	void test_role();
	void test_isShared();
	void test_lastProbed();
	void test_addSourceDir();
	void test_sourceDir();
	void test_removeSourceDir();
	void test_copy();
};

LibraryTest::LibraryTest() {}

LibraryTest::~LibraryTest() {}

void LibraryTest::initTestCase() {}

void LibraryTest::cleanupTestCase() {}

void LibraryTest::test_id() {
	QVERIFY(model1.id() != id);
	model1.setId(id);
	QCOMPARE(model1.id(), id);
}

void LibraryTest::test_name() {
	QVERIFY(model1.name() != name);
	QSignalSpy spy(&model1, SIGNAL(nameChanged()));
	model1.setName(name);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(model1.name(), name);
}

void LibraryTest::test_role() {
	QVERIFY(model1.role() != role);
	model1.setRole(role);
	QCOMPARE(model1.role(), role);
}

void LibraryTest::test_isShared() {
	QVERIFY(model1.isShared() != shared);
	QSignalSpy spy(&model1, SIGNAL(isSharedChanged()));
	model1.setShared(shared);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(model1.isShared(), shared);
}

void LibraryTest::test_lastProbed() {
	QVERIFY(model1.probe()->lastProbed() != lastprobed);
	QSignalSpy spy(model1.probe(), SIGNAL(lastProbedChanged()));
	model1.probe()->setLastProbed(lastprobed);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(model1.probe()->lastProbed(), lastprobed);
}

void LibraryTest::test_addSourceDir() {
	QVERIFY(model1.sourceDir().isEmpty());
	QSignalSpy spy(&model1, SIGNAL(sourceDirChanged()));
	QCOMPARE(model1.addSourceDir(source), true);
	QCOMPARE(spy.count(), 1);
}

void LibraryTest::test_sourceDir() { QCOMPARE(model1.sourceDir(), sourceDir); }

void LibraryTest::test_removeSourceDir() {
	QVERIFY(!model1.sourceDir().isEmpty());
	QSignalSpy spy(&model1, SIGNAL(sourceDirChanged()));
	QCOMPARE(model1.removeSourceDir(source), true);
	QCOMPARE(spy.count(), 1);
}

void LibraryTest::test_copy() {
	QVERIFY(model2.id() != id);
	model2 = model1;
	QCOMPARE(model2.id(), model1.id());
}

QTEST_APPLESS_MAIN(LibraryTest)

#include "tst_librarytest.moc"

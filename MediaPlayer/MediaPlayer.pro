TEMPLATE = subdirs

SUBDIRS = \
    Application \
    Core \
    DesignLibrary \
    ExpressionLibrary \
    UnitTest

Application.depends = Core
UnitTest.depends = Core
Core.depends = DesignLibrary ExpressionLibrary

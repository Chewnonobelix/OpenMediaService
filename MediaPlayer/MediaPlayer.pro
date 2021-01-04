TEMPLATE = subdirs

SUBDIRS = \
    Application \
    Core \
    DesignLibrary \
    ExpressionLibrary \
    UnitTest \
    UxComponent

Application.depends = Core
UnitTest.depends = Core
Core.depends = DesignLibrary ExpressionLibrary UxComponent

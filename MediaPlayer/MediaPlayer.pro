TEMPLATE = subdirs

SUBDIRS = \
    DesignLibrary \
    ExpressionLibrary \
    UxComponent \
    Core \
    Plugins \
    UnitTest \
    ManulTest \
    Application \

Application.depends = Core
UnitTest.depends = Core Plugins
Core.depends = DesignLibrary ExpressionLibrary UxComponent
Plugins.depends = Core UxComponent

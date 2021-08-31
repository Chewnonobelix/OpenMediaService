#pragma once

#include "variantequalexpression.h"
#include "variantinferiorexpression.h"
#include "variantsuperiorexpression.h"
#include "startexpression.h"
#include "endexpression.h"
#include "containexpression.h"
#include "regexpression.h"
#include <Core/valueexpression.h>
#include <Operation/Logic/orexpression.h>
#include <Operation/Logic/andexpression.h>

class ExpressionFactory
{
public:
    ExpressionFactory() = default;

    static QSharedPointer<Expression<bool>> createInferior(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createSuperior(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createEqual(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createInferiorEqual(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createSuperiorEqual(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createStart(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createEnd(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createContain(QVariant&, QVariant&);
    static QSharedPointer<Expression<bool>> createReg(QVariant&, QVariant&);
};


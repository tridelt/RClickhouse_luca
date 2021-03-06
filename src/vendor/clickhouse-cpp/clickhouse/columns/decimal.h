#pragma once

#include "column.h"
#include "numeric.h"

namespace clickhouse {

/**
 * Represents a column of decimal type.
 */
class ColumnDecimal : public Column {
public:
    ColumnDecimal(size_t precision, size_t scale);

    void Append(const BigInt& value);
    void Append(const std::string& value);

    BigInt At(size_t i) const;

public:
    void Append(ColumnRef column) override;
    bool Load(CodedInputStream* input, size_t rows) override;
    void Save(CodedOutputStream* output) override;
    void Clear() override;
    size_t Size() const override;
    ColumnRef Slice(size_t begin, size_t len) override;

private:
    /// Depending on a precision it can be one of:
    ///  - ColumnInt32
    ///  - ColumnInt64
    ///  - ColumnInt128
    ColumnRef data_;

    explicit ColumnDecimal(TypeRef type); // for `Slice(…)`
};

}

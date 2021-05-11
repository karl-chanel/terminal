/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- AttrRow.hpp

Abstract:
- contains data structure for the attributes of one row of screen buffer

Author(s):
- Michael Niksa (miniksa) 10-Apr-2014
- Paul Campbell (paulcam) 10-Apr-2014

Revision History:
- From components of output.h/.c
  by Therese Stowell (ThereseS) 1990-1991
- Pulled into its own file from textBuffer.hpp/cpp (AustDi, 2017)
--*/

#pragma once

#include "til/rle.h"
#include "TextAttribute.hpp"

class ATTR_ROW final
{
    using rle_vector = til::small_rle<TextAttribute, UINT, 1>;

public:
    using const_iterator = rle_vector::const_iterator;

    ATTR_ROW(const UINT cchRowWidth, const TextAttribute attr);

    ~ATTR_ROW() = default;

    ATTR_ROW(const ATTR_ROW&) = default;
    ATTR_ROW& operator=(const ATTR_ROW&) = default;
    ATTR_ROW(ATTR_ROW&&)
    noexcept = default;
    ATTR_ROW& operator=(ATTR_ROW&&) noexcept = default;

    TextAttribute GetAttrByColumn(const size_t column) const;

    std::vector<uint16_t> GetHyperlinks();

    bool SetAttrToEnd(const UINT iStart, const TextAttribute attr);
    void ReplaceAttrs(const TextAttribute& toBeReplacedAttr, const TextAttribute& replaceWith);

    void Resize(const size_t newWidth);

    void Replace(const size_t beginIndex, const size_t endIndex, const TextAttribute& newAttr);

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    friend bool operator==(const ATTR_ROW& a, const ATTR_ROW& b) noexcept;
    friend class ROW;

private:
    void Reset(const TextAttribute attr);

    rle_vector _data;

#ifdef UNIT_TESTING
    friend class CommonState;
#endif
};

#pragma once
#include "style/Style.hpp"

namespace summit::ui {
    /**
    @brief Adds a UI style.
    @param style The style to add. Duplicates will be rejected.
    @return Whether it added successfully or not.
    */
    bool addStyle(styles::Style *style);

    /**
    @brief Gets a UI style by ID.
    @param id The id of the style to get.
    @return The style with the id, or nullptr if none.
    */
    styles::Style *getStyle(std::string id);

    /**
    @brief Gets the current UI style.
    @return The style currently used, or nullptr if none.
    */
    styles::Style *getStyle();

    /**
    @brief Sets the current UI style.
    @param id The id of the style to use. This style must already be added.
    @return Whether it set successfully or not.
    */
    bool setStyle(std::string id);

    #define RegisterStyle(T) $on_mod(Loaded) { addStyle(new T); }
}
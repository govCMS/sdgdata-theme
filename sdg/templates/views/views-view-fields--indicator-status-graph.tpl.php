<?php

/**
 * @file
 * Displays indicator status as a pie graph.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw:
 *     The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler:
 *     The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix:
 *     A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 * - $percentage: Calculated percentage the entry represents.
 *
 * @ingroup views_templates
 */
?>

<div class="indicator-donut__wrapper">

  <div class="indicator-donut" data-value="<?php print round($percentage); ?>"></div>

  <div class="indicator-donut__content status-palette--<?php print $row->field_data_field_machine_name_field_machine_name_value; ?>">
    <span class="indicator-donut__count inherit-color"><?php print $row->field_indicator_status_taxonomy_term_data_nid; ?></span>
    <span class="indicator-donut__title"><?php print $row->taxonomy_term_data_name; ?></span>
    <span class="indicator-donut__percent"><?php print round($percentage); ?>%</span>
  </div>

</div>

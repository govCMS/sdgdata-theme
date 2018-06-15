<?php

/**
 * @file
 * Outputs the virew row with indicator stats and a line graph.
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
 * - $indicators: Custom built array of indicator counts and percentages.
 * - $indicator_count_link: Total number of indicators linked to the goal.
 *
 * @ingroup views_templates
 */
?>

<?php if ($indicator_count_link) : ?>
  <div class="indicator-stats__total">
    <?php print $indicator_count_link; ?>
  </div>
<?php endif; ?>

<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
  <?php print $field->label_html; ?>
  <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>

<div class="indicator-stats">
  <?php foreach($indicators as $label => $indicator) : ?>
  <div class="indicator-stats__row">
    <span class="indicator-stats__count color__<?php print $indicator['class']; ?>"><?php print $indicator['count']?></span>
    <?php print $indicator['label']; ?>
    <?php print $indicator['percent']; ?>%
  </div>
  <?php endforeach; ?>
</div>

<div class="line-graph">
  <?php $count = 0; ?>
  <?php foreach($indicators as $label => $indicator) : ?>
    <?php if ($indicator['percent']) : ?>
      <div class="line-graph__item color__<?php print $indicator['class']; ?> line-graph__item--<?php print $count; ?>" style="width: <?php print $indicator['percent']; ?>%"></div>
      <?php $count++; ?>
    <?php endif; ?>
  <?php endforeach; ?>
</div>

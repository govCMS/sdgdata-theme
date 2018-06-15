<?php
/**
 * @file
 * Preprocessors for fields.
 */

/**
 * Implements template_preprocess_field.
 */
function sdg_preprocess_field(&$variables, $hook) {
  $element = $variables['element'];
  $hook = __FUNCTION__ . "__{$element['#field_name']}";

  if (is_callable($hook)) {
    $hook($variables);
  }
}

/**
 * Implements template_preprocess_field__FIELD-NAME.
 *
 * Adds a prefix to the responsible agency field.
 */
function sdg_preprocess_field__field_agency(&$variables) {
  $element = $variables['element'];
  $items = &$variables['items'];

  // Check if we're viewing an Indicator node.
  if ($element['#bundle'] == 'indicator' && $element['#view_mode'] == 'full') {
    try {
      $entity = $element['#object'];
      $entity_wrapper = entity_metadata_wrapper($element['#entity_type'], $entity);

      // Loop over agencies linking them to the value in their URL field as
      // opposed to the full node.
      foreach ($items as $item_delta => &$item) {
        $item = array(
          '#theme' => 'sdg_entityreference_link',
          '#entity' => $entity_wrapper->field_agency[$item_delta]->value(),
          '#entity_type' => 'node',
          '#field' => 'field_url',
        );
      }
    }
    catch (EntityMetadataWrapperException $e) {
      watchdog('sdg', 'EntityMetadataWrapper exception in %function() <pre>@trace</pre>', array(
        '%function' => __FUNCTION__,
        '@trace' => $e->getTraceAsString(),
      ), WATCHDOG_ERROR);
    }

    // Generate the markup to prefix the list of agencies.
    // Field isn't rendered if there are no agencies to list so markup
    // won't display either.
    $markup = array('#markup' => t('The agency responsible for this data entry is&nbsp;'));

    // Insert the markup to the very start of the item listing.
    array_unshift($items, $markup);
  }
}

/**
 * Implements template_preprocess_field__FIELD-NAME.
 *
 * Removes letters (e.g. a), b), etc) from the beginning of caveat sentences.
 */
function sdg_preprocess_field__field_indicator_status_caveat(&$variables) {
  $element = $variables['element'];
  $items = &$variables['items'];

  if ($element['#bundle'] === 'indicator') {
    $items[0]['#markup'] = trim(preg_replace("/^[a-z]\)/i", '', $items[0]['#markup']));
  }
}

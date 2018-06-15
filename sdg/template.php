<?php

/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728096
 */

$theme_dir = drupal_get_path('theme', 'sdg');

/**
 * Include helpers from the helpers folder.
 *
 * Naming convention for alter files should be something like this:
 * {helper}.inc.
 */
foreach (file_scan_directory($theme_dir . '/helpers', '/.+\.inc/i') as $file) {
  require_once $file->uri;
}

/**
 * Include preprocessors.
 *
 * For better organisation and to prevent this file from becoming monolithic
 * preprocessors should be placed in the preprocess folder. This code will then
 * include all those files as if the lived here.
 *
 * Naming convention for preprocess files should be something like this:
 * {theme_hook}.preprocess.inc
 */
foreach (file_scan_directory($theme_dir . '/preprocess', '/.+\.inc/i') as $file) {
  require_once $file->uri;
}

/**
 * Include alters from the alter folder.
 *
 * Naming convention for alter files should be something like this:
 * {theme_hook}.alter.inc.
 */
foreach (file_scan_directory($theme_dir . '/alter', '/.+\.inc/i') as $file) {
  require_once $file->uri;
}

/**
 * Implements hook_theme().
 *
 * All templates for theme keys defined here should live in templates/custom.
 */
function sdg_theme($existing, $type, $theme, $path) {
  return array(
    'sdg_entityreference_link' => array(
      'variables' => array(
        'entity' => NULL,
        'entity_type' => '',
        'field' => '',
      ),
      'function' => 'theme_sdg_entityreference_link',
    ),
    'sdg_indicator_status' => array(
      'variables' => array(
        'indicator' => NULL,
      ),
      'path' => $path . '/templates/custom',
      'template' => 'sdg-indicator-status',
    ),
    'sdg_search_form' => array(
      'variables' => array(),
      'path' => $path . '/templates/custom',
      'template' => 'sdg-search-form',
    ),
  );
}

/**
 * Implements theme_breadcrumb().
 */
function sdg_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' <i class="fa-icon-chevron-right"></i> ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Implements theme_sdg_entityreference_link().
 */
function theme_sdg_entityreference_link($variables) {
  $entity = $variables['entity'];
  $entity_type = $variables['entity_type'];
  $field_url = $variables['field'];

  $output = '';

  try {
    $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
    $entity_url = $entity_wrapper->{$field_url}->value();

    if (!empty($entity_url['url'])) {
      $output = theme('link', array(
        'text' => $entity_wrapper->label(),
        'path' => $entity_url['url'],
        'options' => array(
          'attributes' => array('target' => '_blank'),
          'html' => FALSE,
        ),
      ));
    }
    else {
      $output = check_plain($entity_wrapper->label());
    }
  }
  catch (EntityMetadataWrapperException $e) {
    watchdog('sdg', 'EntityMetadataWrapper exception in %function() <pre>@trace</pre>', array(
      '%function' => __FUNCTION__,
      '@trace' => $e->getTraceAsString(),
    ), WATCHDOG_ERROR);
  }

  return $output;
}

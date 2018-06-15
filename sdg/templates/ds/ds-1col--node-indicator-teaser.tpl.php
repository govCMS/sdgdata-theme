<?php

/**
 * @file
 * Display Suite 1 column template.
 *
 * Template is being overriden to add an '<a>' wrapper around the content and
 * make the entire teaser link off to the node.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <a href="<?php print url('node/' . $nid); ?>" class="indicator-teaser__wrapper">
    <?php print $ds_content; ?>
  </a>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

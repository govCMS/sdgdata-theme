<?php

/**
 * @file
 * Data sources template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="col <?php print $classes;?> clearfix">

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>

<?php if($content) : ?>
  <div class="data-sources__row">
    <div class="data-sources__column data-sources__label data-sources__label--first"></div>
    <div class="data-sources__column data-sources__label data-sources__label--first">
      Source <?php print $delta; ?>
    </div>
  </div>
  <?php foreach($content as $field => $item) : ?>
    <div class="data-sources__row">
      <div class="data-sources__column data-sources__label">
        <?php print $item['#title']; ?>
      </div>
      <div class="data-sources__column data-sources__text">
        <?php print render($item); ?>
      </div>
    </div>
  <?php endforeach; ?>
<?php endif; ?>

</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

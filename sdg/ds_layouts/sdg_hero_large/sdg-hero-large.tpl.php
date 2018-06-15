<?php
/**
 * @file
 *
 * Hero large.
 */
?>
<div class="hero hero--large no-constraints" >

  <div class="hero__image js-img-to-bg">
     <?php print $image; ?>
  </div>

  <div class="hero__content-outer constraints">
    <div class="hero__content-inner">
      <?php print $main_content; ?>
      <a href="#main-content" class="hero__scroll-btn js-scroll-to"></a>
    </div>
  </div>

</div>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

<?php
// $Id$

/**
 * @file
 * Contains a collection of Pasargad Bank Paypaad Payment API internal helpers.
 */

/**
 * Internal helper to build XML string as per required by gateway.
 *
 * @param $content
 *   Invoice array as per documented in paypaad_xml().
 * @param $items
 *   Products array as per documented in paypaad_xml().
 * @param $validate
 *   Whether to validate the generated XML using gateway
 *   provided DTD or not.
 *
 * @return
 *   $array corresponding XML.
 *
 * @see paypaad_xml()
 * @see _paypaad_xml_validate()
 * @see _paypaad_xml_template_load()
 */
function _paypaad_xml_build(&$content, &$items, $validate = FALSE) {
  // XML document header.
  $xml = '<?xml version="1.0" encoding="UTF-8" ?>';
  // In case of empty $items, remove %items% placeholder.
  $content['items'] = '';
  // Walk through the products array.
  if (!empty($items)) {
    $count = 1;
    foreach ($items as $index => $product) {
      $content['items'] .= _paypaad_xml_template_load((array) $product, 'item');
    }
  }
  // Build invoice XML body.
  $xml .= _paypaad_xml_template_load($content, 'invoice');

  // Validate generated XML against its DTD, if requested so.
  return $validate ? (_paypaad_xml_validate($xml) ? $xml : FALSE) : $xml;
}

/**
 * Internal helper that loads a XML template with given data.
 *
 * @param $data
 *   An array of keyed values to be used as a dictionary.
 *   e.g. Every %blah% placeholder in $template will be filled
 *   with the value of 'blah' key in the $data array.
 * @param $template
 *   XML template identifier to load its string with $data.
 *   Accepted values are as per documented in _paypaad_xml_template().
 * @param $eol_strip
 *   Whether to strip OS EOL chars or not.
 *
 * @return
 *   Either the requested XML template or FALSE on fail.
 *
 * @see _paypaad_xml_build()
 * @see _paypaad_xml_template()
 */
function _paypaad_xml_template_load($data, $template, $eol_strip = TRUE) {
  // Get XML template string.
  $template = _paypaad_xml_template($template, $eol_strip);
  // Not enough minerals?!
  if (!$data || !$template) {
    return FALSE;
  }
  // Walk through the array.
  foreach ($data as $key => $value) {
    $template = str_replace("%$key%", $value, $template);
  }
  return $template;
}

/**
 * Internal static cache helper that returns a XML template.
 *
 * Avoids API change maintenance disasters!
 *
 * @param $id
 *   XML template identifier to return.
 *   - invoice: returns invoice XML template.
 *   - item: returns an item XML template. (product)
 * @param $eol_strip
 *   Whether to strip OS EOL chars or not.
 *
 * @return
 *   Either the requested XML template or FALSE on fail.
 *
 * @see _paypaad_xml_build()
 */
function _paypaad_xml_template($id, $eol_strip = TRUE) {
  static $templates = array();

  // Implementing static cache.
  if (!$templates[$id]) {
    // Get requested XML template path.
    $path = drupal_get_path('module', 'paypaad') . "/xml/$id.tpl.xml";
    // Check if the XML template file is readable.
    if (is_readable($path)) {
      $templates[$id] = file_get_contents($path);
    }
    else {
      return FALSE;
    }
  }
  // Return XML template string as requested.
  return $eol_strip ? str_replace(array("\r", "\n"), '', $templates[$id]) : $templates[$id];
}

/**
 * Internal helper that validates a XML string against given DTD.
 *
 * @param $xml
 *   XML string to be validated.
 * @param $root
 *   XML root node name.
 * @param $dtd_path
 *   Accessible system path of DTD file.
 *
 * @return
 *   Boolean value.
 *
 * @see _paypaad_xml_build()
 * @see http://php.net/manual/en/class.domdocument.php
 * @see http://us.php.net/manual/en/domdocument.schemavalidate.php
 *
 * @todo
 *   If possible, generate appropriate XSD file and
 *   validate against that using DOMDocument::schemaValidate.
 */
function _paypaad_xml_validate($xml, $root = 'invoice', $dtd_path = FALSE) {
  // Check DTD file path.
  $dtd_path = $dtd_path ? $dtd_path : drupal_get_path('module', 'paypaad') . '/xml/protocol.dtd';
  if (!is_readable($dtd_path)) {
    return FALSE;
  }

  // Return XML validation results:
  // Here we should use a trick and
  // then validation will be simply done.
  // DTD is pretty damn old, XSD might be a
  // better choice here.
  //
  // Instantiate a DOMDocument object based
  // on passed XML string, if the $xml string
  // has its own DTD included, overwrite that
  // with the one specified in $dtd_path file.
  $dom = new DOMDocument();
  $dom->loadXML($xml);
  // Instantiate a new DOMDocument with $dtd_path DTD.
  $dom_creator = new DOMImplementation();
  $dom_doctype = $dom_creator->createDocumentType($root, NULL, $dtd_path);
  $new_dom  = $dom_creator->createDocument(NULL, NULL, $dom_doctype);
  $new_dom->encoding = 'UTF-8';
  // Loading $xml directly into the new object will
  // cause $new_dom's DTD ($dtd_path) to be overwritten
  // by the original DTD specified in passed XML string.
  $dom_node = $dom->getElementsByTagName($root)->item(0);
  $new_dom_node = $new_dom->importNode($dom_node, TRUE);
  $new_dom->appendChild($new_dom_node);
  // Validate and return results.
  return $new_dom->validate();
}

/**
 * Internal helper to parse a well-formed XML string into an array.
 *
 * @param $xml
 *   XML string to be parsed.
 *
 * @return
 *   Passed XML string corresponding array.
 *
 * @see paypaad_trace()
 * @see http://php.net/manual/en/book.json.php
 */
function _paypaad_xml_parse($xml) {
  return json_decode(json_encode(simplexml_load_string($xml)), TRUE);
}

/**
 * Internal helper to perform a cURL POST request.
 *
 * @param $destination
 *   cURL destination URI.
 * @param $params
 *   Parameters to be sent in a HTTP POST operation,
 *   As per defined in CURLOPT_POSTFIELDS docs.
 *
 * @return
 *   Either the request response string or FALSE on fail.
 *
 * @see paypaad_trace()
 * @see paypaad_request()
 * @see http://php.net/manual/en/function.curl-setopt.php
 */
function _paypaad_curl($destination, $params = '') {
  // Check cURL dependency.
  if (!extension_loaded('curl')) {
    return FALSE;
  }

  // Initiate cURL session, set options.
  $curl = curl_init($destination);
  curl_setopt($curl, CURLOPT_HEADER, FALSE);
  curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
  // Follow any 'Location:' header,
  // CURLOPT_MAXREDIRS won't be set.
  curl_setopt($curl, CURLOPT_FOLLOWLOCATION, TRUE);
  // Set POST request options.
  curl_setopt($curl, CURLOPT_POST, TRUE);
  // I wonder why it's not working with associative arrays, might
  // be a HTTP header "Expect:" issue. Read CURLOPT_POSTFIELDS option
  // description at: http://php.net/manual/en/function.curl-setopt.php
  curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($params));
  // Run rabbit, run!
  $response = curl_exec($curl);

  // Close the session.
  curl_close($curl);
  // And return the response.
  return (string) $response;
}


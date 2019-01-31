
<?php
$realm = 'Restricted area';

// user names and passwords should be more secure
$users = array('admin' => 'mypass', 'guest' => 'guest');

if (empty($_SERVER['PHP_AUTH_DIGEST'])) {
    header('HTTP/1.1 401 Unauthorized');
    // using sprintf is preferred over concatentation
    // nonce should be hashed id, example: $nonce = md5(uniqid())
    // opaque should be hashed id
    // qop should be set to auth-int to enforce integrity protection of the response
    header('WWW-Authenticate: Digest realm="'.$realm.
           '",qop="auth",nonce="'.uniqid().'",opaque="'.md5($realm).'"');

    // Content-Type header is missing
    
    // note: regular echo+exit looks better than "fatal" die
    die('Text to send if user hits Cancel button');
}

if (!($data = http_digest_parse($_SERVER['PHP_AUTH_DIGEST'])) ||
    !isset($users[$data['username']])
	)
    die('Wrong Credentials!');


// A1 should not use the password sent by client, it should get
// hashed password from server's database and use it as third
// argument in added sprintf, also realm should be parsed from the data
$A1 = md5($data['username'] . ':' . $realm . ':' . $users[$data['username']]);
// A2 should contain a hash of the response body (auth-int case)
$A2 = md5($_SERVER['REQUEST_METHOD'].':'.$data['uri']);
$valid_response = md5($A1.':'.$data['nonce'].':'.$data['nc'].':'.$data['cnonce'].':'.$data['qop'].':'.$A2);

if ($data['response'] != $valid_response)
    die('Wrong Credentials!');

echo 'You are logged in as: ' . $data['username'];


function http_digest_parse($txt)
{
    // realm is missing in the array
    $needed_parts = array('nonce'=>1, 'nc'=>1, 'cnonce'=>1, 'qop'=>1, 'username'=>1, 'uri'=>1, 'response'=>1);
    $data = array();
    $keys = implode('|', array_keys($needed_parts));

    preg_match_all('@(' . $keys . ')=(?:([\'"])([^\2]+?)\2|([^\s,]+))@', $txt, $matches, PREG_SET_ORDER);

    foreach ($matches as $m) {
        $data[$m[1]] = $m[3] ? $m[3] : $m[4];
        unset($needed_parts[$m[1]]);
    }

    return $needed_parts ? false : $data;
}
?>
